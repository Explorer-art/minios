#pragma once

#include <kernel/disk.h>

#define BUFFER 10240
#define USERLAND_ADDR 0x00005400

void execute_program(const char* filename);
