#include <stdio.h>
#include <stdint.h>
#include <kernel/disk.h>
#include <kernel/fat.h>
#include <kernel/tty.h>
#include <kernel/terminal.h>

void far* g_data = (void far*) 0x00500200;

void _cdecl kmain() {
	// Инициализация TTY
	tty_initialize();
	
	DISK disk;

	if (!DISK_Initialize(&disk, 0)) {
		printf("Disk init error");
		goto end;
		
	}

	DISK_ReadSectors(&disk, 19, 1, g_data);

	if (!FAT_Initialize(&disk)) {
		printf("FAT init error");
		goto end;
	}

	FAT_File far* fd = FAT_Open(&disk, "/");
	FAT_DirectoryEntry entry;
	int i = 0;

	while (FAT_ReadEntry(&disk, fd, &entry) && i++ < 5) {
		printf("Filename: ");
		
		for (int i = 0; i < 11; i++) {
			putchar(entry.Name[i]);	
		}

		printf("\n");
	}

	FAT_Close(fd);

	char buffer[128];
	uint32_t read_bytes;
	fd = FAT_Open(&disk, "dir/file.txt");

	while ((read_bytes = FAT_Read(&disk, fd, sizeof(buffer), buffer))) {
		for (uint32_t i = 0; i < read_bytes; i++) {
			if (buffer[i] == '\n') {
				putchar('\r');
			}
			
			putchar(buffer[i]);
		}
	}

	// Передача управления терминалу
	//terminal_main();
end:
	for(;;);
}
