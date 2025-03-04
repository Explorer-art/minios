#pragma once

#include <stdint.h>

typedef struct {
	uint32_t StartAddr;
	uint32_t Size;
} MemoryData;

void* mem_alloc(uint32_t size);
void mem_free(uint32_t* ptr);
