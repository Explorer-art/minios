#include "stdint.h"
#include "stdio.h"

void _cdecl cstart_(uint16_t BootDrive) {
	puts("Hello world from STAGE2!");

	for (;;);
}