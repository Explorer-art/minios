#include <stdint.h>
#include <kernel/disk.h>
#include <kernel/fat.h>
#include <kernel/tty.h>
#include <kernel/syscall.h>
#include <kernel/shell.h>
#include <kernel/executor.h>

void _cdecl kmain() {
	DISK disk;

	kprintf("Disk init...\n");

	if (!DISK_Init(&disk, 0)) {
		kprintf("ERROR! Disk init failed\n");
		goto end;
	}

	kprintf("FAT init...\n");

	if (!FAT_Init(&disk)) {
		kprintf("ERROR! FAT init failed\n");
		goto end;
	}

	kprintf("Syscall init...\n");

	if (!Syscall_Init()) {
		kprintf("ERROR! Syscall init failed\n");
		goto end;
	}

	execute_program(disk, "program.bin");

	// Передача управления терминалу
	// shell_main(disk);

	kprintf("System halted\n");
end:
	for(;;);
}
