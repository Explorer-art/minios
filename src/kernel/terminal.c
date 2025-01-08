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

bool cd(char* command) {
	if (strcmp(string_split(command, ' ', 1), command) == 0) {
		printf("Incorrect command format!\n");
		printf("Example: cd <dir>\n");
		return false;
	}

	char dir[256] = {0};

	int i = 3;
	int j = 0;

	while (command[i] != '\0') {
		dir[j] = command[i];
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
	printf("INFO:\n\nSystem: Minio\nVersion: %s\nAuthor: Truzme_\n", VERSION);
	return true;
}

bool echo(char* command) {
	if (strcmp(string_split(command, ' ', 1), command) == 0) {
		printf("Incorrect command format!\n");
		printf("Example: echo <text>\n");
		return false;
	}

	for (int i = 5; i < strlen(command); i++) {
		putchar(command[i]);
	}

	putchar('\n');
	putchar('\r');

	return true;
}

bool clear() {
	tty_clear();
	return true;
}

bool help();

static const Command_Map commands[] = {
	{"help", help},
	{"ls", ls},
	{"cd", cd},
	{"info", info},
	{"echo", echo},
	{"clear", clear}
};

bool help() {
	printf("Help on commands:\n\n");
	
	for (int i = 0; i < sizeof(commands) / sizeof(Command_Map); i++) {
		printf("%s\n", commands[i]);
	}
	
	return true;
}

void terminal_main(DISK disk) {
	g_disk = disk;
	char* command;
	char far* arg_1;

	printf("Welcome to Minio!\n\n");

	while (true) {
		printf("%s > ", g_current_dir);

		command = tty_gets();

		arg_1 = (char far*) string_split(command, ' ', 0);

		if (strcmp(arg_1, "help") == 0) {
			help();
		} else if (strcmp(arg_1, "ls") == 0) {
			ls();
		} else if (strcmp(arg_1, "cd") == 0) {
			cd(command);
		} else if (strcmp(arg_1, "info") == 0) {
			info();
		} else if (strcmp(arg_1, "echo") == 0) {
			echo(command);
		} else if (strcmp(arg_1, "clear") == 0) {
			clear();
		} else {
			printf("Unknown command\n");
		}
	}
}
