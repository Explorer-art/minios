#include <stdio.h>
#include <stdint.h>
#include <kernel/disk.h>
#include <kernel/fat.h>
#include <kernel/tty.h>
#include <kernel/terminal.h>

void far* g_data = (void far*)0x00500200;

void _cdecl kmain() {
	// Инициализация TTY
	tty_initialize();
	
	DISK disk;

	if (!DISK_Initialize(&disk, 0)) {
		printf("Disk init error");
		goto end;
		
	}

	if (!FAT_Initialize(&disk)) {
		printf("FAT init error");
		goto end;
	}

	// Передача управления терминалу
	terminal_main(disk);
end:
	for(;;);
}

