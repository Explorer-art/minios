#pragma once

#include <kernel/disk.h>

typedef bool (*command_func_t)(char*);

typedef struct {
	char* command;
	command_func_t func;
} Command_Map;

void terminal_main(DISK disk);
