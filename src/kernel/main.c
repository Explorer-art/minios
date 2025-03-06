#include <stdint.h>
#include <kernel/disk.h>
#include <kernel/fat.h>
#include <kernel/tty.h>
#include <kernel/syscalls.h>
#include <kernel/terminal.h>
#include <utils.h>

puts_syscall_ptr far* puts_syscall = (puts_syscall_ptr far*)0x0055270;

void _cdecl kmain() {
	DISK disk;

	if (!DISK_Init(&disk, 0)) {
		tty_printf("Disk init error\n");
		goto end;
		
	}

	if (!FAT_Init(&disk)) {
		tty_printf("FAT init error\n");
		goto end;
	}

	if (!Syscall_Init()) {
		tty_printf("Syscall init error\n");
		goto end;
	}

	(*puts_syscall)("Hello world!\n");

	// Передача управления терминалу
	// terminal_main(disk);
end:
	for(;;);
}
