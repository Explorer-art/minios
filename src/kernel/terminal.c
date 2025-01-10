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
	printf("%s\n", g_current_dir);
	
	memset(g_data, 0, 512);
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

	char buffer[256] = {0};

	if (strcmp(args[1], "..") == 0) {
		if (strcmp(g_current_dir, '/') == 0) {
			return false;
		}

		char** dir_args = string_split(g_current_dir, '/');
		int g_current_dir_lenght = strlen(g_current_dir);
		int dir_args_count = get_args_count(dir_args);

		buffer[0] = '/';

		for (int i = 0; i < dir_args_count - 1; i++) {
			strcat(buffer, dir_args[i]);
		}

		memset(g_current_dir, g_current_dir_lenght, 0);
		strcpy(g_current_dir, buffer);
	} else {
		int i = 0;
		int j = 0;

		if (strcmp(g_current_dir, "/") != 0) {
			buffer[j] = '/';
			j++;
		}

		while (args[1][i] != '\0') {
			buffer[j] = args[1][i];
			i++;
			j++;
		}
			
		if (strlen(g_current_dir) + strlen(buffer) > sizeof(g_current_dir) - 1) {
			return false;
		}

		strcat(g_current_dir, buffer);
	}

	return true;
}

bool cat(char** args) {
	char buffer[256] = {0};

	memset(g_data, 0, 512);
	DISK_ReadSectors(&g_disk, 19, 1, g_data);

	if (args[1][0] == '/') {
		strcpy(buffer, args[1]);
	} else {
		strcpy(buffer, g_current_dir);
		strcat(buffer, "/");
		strcat(buffer, args[1]);
	}

	FAT_File far* fd = FAT_Open(&g_disk, buffer);
	uint32_t read_bytes;

	memset(buffer, 0, sizeof(buffer));

	while ((read_bytes = FAT_Read(&g_disk, fd, sizeof(buffer), buffer))) {
		for (uint32_t i = 0; i < read_bytes; i++) {
			if (buffer[i] == '\n') {
				putchar('\r');
			}

			putchar(buffer[i]);
		}
	}

	printf("\n\n");

	FAT_Close(fd);
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
	{"cat", "Read file", cat},
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

	tty_clear();

	printf("Welcome to Minios!\n\n");

	while (true) {
		printf("%s %s > ", PROMPT, g_current_dir);

		command = tty_gets();
		command_handle(command);
	}
}
