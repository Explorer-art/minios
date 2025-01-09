#include <stdio.h>
#include <stdint.h>
#include <kernel/disk.h>
#include <kernel/fat.h>
#include <kernel/tty.h>
#include <kernel/terminal.h>
#include <kernel/allocator.h>

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

	//tty_clear();

	// Mem_Print();

	// uint32_t* ptr = 0x30000;

	//*ptr = 123;

	// printf("Address: %x\n", ptr);
	//printf("Value: %d\n", *ptr);

	// Mem_Free(ptr);

	uint32_t* ptr1 = malloc(4);

	*ptr1 = 123;
	printf("Address: %d\n", ptr1);
	printf("Value: %d\n\n", *ptr1);

	uint32_t* ptr2 = malloc(4);

	*ptr2 = 123;
	printf("Address: %d\n", ptr2);
	printf("Value: %d\n\n", *ptr2);

	free(ptr1);

	uint32_t* ptr3 = malloc(4);

	*ptr3 = 123;
	printf("Address: %d\n", ptr3);
	printf("Value: %d\n", *ptr3);

	// printf("Memory freed!\n");

	// Mem_Print();

	// Передача управления терминалу
	//terminal_main(disk);
end:
	for(;;);
}
