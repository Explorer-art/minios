#pragma once

#include <stdint.h>

uint32_t align(uint32_t number, uint32_t alignTo);
char** string_split(char* str, char delim);
void free_split(char** args);
int get_args_count(char** args);
