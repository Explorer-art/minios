#include <stdint.h>
#include <kernel/disk.h>
#include <kernel/fat.h>
#include <kernel/tty.h>
#include <kernel/syscall.h>
#include <kernel/terminal.h>
#include <kernel/executor.h>
#include <utils.h>

void _cdecl kmain() {
	DISK disk;

	if (!DISK_Init(&disk, 0)) {
		kernel_printf("Disk init error\n");
		goto end;
		
	}

	if (!FAT_Init(&disk)) {
		kernel_printf("FAT init error\n");
		goto end;
	}

	if (!Syscall_Init()) {
		kernel_printf("Syscall init error\n");
		goto end;
	}

	// kernel_printf("Hello from kernel!\n");

	execute(disk, "/program.bin");

	// Передача управления терминалу
	// terminal_main(disk);
end:
	for(;;);
}
