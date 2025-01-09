#pragma once

#include <stdint.h>

typedef struct {
	uint32_t StartAddr;
	uint32_t Size;
} MemoryData;

void* malloc(uint32_t size);
void free(uint32_t* ptr);
