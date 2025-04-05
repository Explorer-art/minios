#pragma once

// 0x00000000 - 0x000003FF - interrupt vector table
// 0x00000400 - 0x000004FF - BIOS data area
// 0x00000500 - 0x00010500 - FAT driver
// 0x00020000 - 0x00024FFF - Kernel
// 0x00025000 - 0x00025399 - Syscall vector table
// 0x00025400 - 0x00026799 - Userland

#define MEMORY_FAT_ADDR		((void far*)0x00500000)         // segment:offset (SSSSOOOO)
#define MEMORY_FAT_SIZE		0x00010000

// 0x00030000 - 0x00080000 - free (327680 bytes)
#define FREE_MIN			0x00030000
#define FREE_MAX			0x00080000

// 0x00080000 - 0x0009FFFF - Extended BIOS data area
// 0x000A0000 - 0x000C7FFF - Video
// 0x000C8000 - 0x000FFFFF - BIOS
