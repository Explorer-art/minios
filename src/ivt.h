#pragma once

#include <stdint.h>

typedef struct {
	uint16_t offset;
	uint16_t segment;
} IVT_Entry;

typedef void (*interrupt_handler_t)(void);

void IVT_Init();
