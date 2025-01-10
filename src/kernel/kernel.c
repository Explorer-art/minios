#include <stdio.h>
#include <stdint.h>
#include <kernel/disk.h>
#include <kernel/fat.h>
#include <kernel/tty.h>
#include <kernel/terminal.h>
#include <utils.h>

void far* g_data = (void far*) 0x00500200;

void _cdecl kmain() {
	DISK disk;

	if (!DISK_Init(&disk, 0)) {
		printf("Disk init error\n");
		goto end;
		
	}

	if (!FAT_Init(&disk)) {
		printf("FAT init error\n");
		goto end;
	}

	// Передача управления терминалу
	terminal_main(disk);
end:
	for(;;);
}
