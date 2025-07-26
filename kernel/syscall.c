#include <kernel/x86.h>
#include <kernel/tty.h>
#include <kernel/allocator.h>
#include <kernel/syscall.h>

Syscalls syscalls = {
	(putchar_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x00),
	(tty_puts_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x04),
	(kprintf_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x08),
	(getchar_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x0C),
	(gets_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x10),
	(malloc_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x14),
	(free_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x18),
	(fat_open_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x1C),
	(fat_read_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x20),
	(fat_close_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x24)
};

bool Syscall_Init() {
	*syscalls.putchar = (putchar_syscall_ptr)&putchar;
	*syscalls.puts = (tty_puts_syscall_ptr)&tty_puts;
	*syscalls.printf = (kprintf_syscall_ptr)&kprintf;
	*syscalls.getchar = (getchar_syscall_ptr)&getchar;
	*syscalls.gets = (gets_syscall_ptr)&tty_gets;
	*syscalls.malloc = (malloc_syscall_ptr)&mem_alloc;
	*syscalls.free = (free_syscall_ptr)&mem_free;
	*syscalls.fat_open = (fat_open_syscall_ptr)&FAT_Open;
	*syscalls.fat_read = (fat_read_syscall_ptr)&FAT_Read;
	*syscalls.fat_close = (fat_close_syscall_ptr)&FAT_Close;

	return true;
}
