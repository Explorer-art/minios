#pragma once

#include <stdint.h>

typedef void* (*malloc_syscall_ptr)(uint32_t size);
typedef void (*free_syscall_ptr)(uint32_t* ptr);

void* malloc(uint32_t size);
void free(uint32_t* ptr);
