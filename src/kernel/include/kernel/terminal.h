#pragma once

#include <kernel/disk.h>

typedef bool (*command_func_t)(char**);

typedef struct {
	char* command;
	char* description;
	command_func_t func;
} CommandData;

void terminal_main(DISK disk);
