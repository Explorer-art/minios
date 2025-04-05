#include <kernel/x86.h>
#include <kernel/tty.h>
#include <kernel/allocator.h>
#include <kernel/syscall.h>

Syscalls syscalls = {
	(putchar_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x00),
	(getchar_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x04),
	(gets_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x08),
	(malloc_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x0C),
	(free_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x10),
	(fat_open_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x14),
	(fat_read_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x18),
	(fat_close_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x1C)
};

bool Syscall_Init() {
	*syscalls.putchar = (putchar_syscall_ptr)&putchar;
	*syscalls.getchar = (getchar_syscall_ptr)&getchar;
	*syscalls.gets = (gets_syscall_ptr)&tty_gets;
	*syscalls.malloc = (malloc_syscall_ptr)&mem_alloc;
	*syscalls.free = (free_syscall_ptr)&mem_free;
	*syscalls.fat_open = (fat_open_syscall_ptr)&FAT_Open;
	*syscalls.fat_read = (fat_read_syscall_ptr)&FAT_Read;
	*syscalls.fat_close = (fat_close_syscall_ptr)&FAT_Close;

	return true;
}
