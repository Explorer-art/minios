#pragma once

#include <stdint.h>

#define MEMORY_SIZE 16384
#define MEMORY_MAX_HANDLES 100

typedef struct {
	uint32_t StartAddr;
	uint32_t Size;
} MemoryData;

void* mem_alloc(uint32_t size);
void mem_free(uint32_t* ptr);
