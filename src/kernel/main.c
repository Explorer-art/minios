#include <stdint.h>
#include <kernel/disk.h>
#include <kernel/fat.h>
#include <kernel/tty.h>
#include <kernel/syscalls.h>
#include <kernel/terminal.h>
#include <utils.h>

printf_syscall_ptr far* printf_syscall = (printf_syscall_ptr far*)0x0055270;

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

	// Передача управления терминалу
	terminal_main(disk);
end:
	for(;;);
}
