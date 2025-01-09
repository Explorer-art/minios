#pragma once

#include <stdint.h>

typedef struct {
	uint32_t StartAddr;
	uint32_t Size;
} MemoryData;

bool Alloc_Initialize();
uint32_t mem_alloc(uint32_t size);
uint32_t mem_free(uint32_t ptr);