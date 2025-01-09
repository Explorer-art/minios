#include <kernel/terminal.h>
#include <kernel/tty.h>
#include <kernel/fat.h>
#include <kernel/disk.h>
#include <kernel/config.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <utils.h>

static DISK g_disk;
static void far* g_data = (void far*) 0x00500200;
static char g_current_dir[256] = "/";

bool ls() {
	DISK_ReadSectors(&g_disk, 19, 1, g_data);

	FAT_File far* fd = FAT_Open(&g_disk, g_current_dir);
	FAT_Entry entry;
	int i = 0;

	while (FAT_ReadEntry(&g_disk, fd, &entry) && i++ < 5) {
		for (int i = 0; i < 11; i++) {
			putchar(entry.Name[i]);
		}

		printf("\n");
	}

	FAT_Close(fd);

	return true;
}

bool cd(char** args) {
	int args_count = get_args_count(args);

	if (args_count < 2) {
		printf("Incorrect command format!\n");
		printf("Example: cd <dir>\n\n");
		return false;
	}

	char dir[256] = {0};

	int i = 3;
	int j = 0;

	while (args[1][i] != '\0') {
		dir[j] = args[1][i];
		i++;
		j++;
	}

	dir[j] = '/';
		
	if (strlen(g_current_dir) + strlen(dir) > sizeof(g_current_dir) - 1) {
		return false;
	}

	strcat(g_current_dir, dir);

	return true;
}

bool info() {
	printf("System: Minios\nVersion: %s\nAuthor: Truzme_\n\n", VERSION);
	return true;
}

bool echo(char** args) {
	int args_count = get_args_count(args);

	if (args_count < 2) {
		printf("Incorrect command format!\n");
		printf("Example: echo <text>\n\n");
		return false;
	}

	for (int i = 1; i < args_count; i++) {
		printf("%s ", args[i]);
	}

	printf("\n\n");

	return true;
}

bool clear() {
	tty_clear();
	return true;
}

bool help();

static const CommandData commands_map[] = {
	{"help", "Help on commands", help},
	{"ls", "Read directory", ls},
	{"cd", "Change directory", cd},
	{"info", "Information about the system", info},
	{"echo", "Print test to the terminal", echo},
	{"clear", "Clear terminal", clear}
};

bool help() {
	for (int i = 0; i < sizeof(commands_map) / sizeof(CommandData); i++) {
		printf("%s - %s\n", commands_map[i].command, commands_map[i].description);
	}

	printf("\n");
	
	return true;
}

bool command_handle(char* command) {
	char** args = string_split(command, ' ');

	for (int i = 0; i < sizeof(commands_map) / sizeof(CommandData); i++) {
		if (strcmp(args[0], commands_map[i].command) == 0) {
			return commands_map[i].func(args);
		}
	}

	printf("Unknown command!\n\n");

	return false;
}

void terminal_main(DISK disk) {
	g_disk = disk;
	char* command;

	printf("Welcome to Minio!\n\n");

	while (true) {
		printf("%s %s > ", PROMPT, g_current_dir);

		command = tty_gets();
		command_handle(command);
	}
}
