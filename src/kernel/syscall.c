#include <kernel/tty.h>
#include <kernel/allocator.h>
#include <kernel/syscall.h>

Syscalls syscalls = {
	(putchar_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x00),
	(puts_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x20),
	(printf_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x40),
	(getchar_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x60),
	(gets_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x80),
	(malloc_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x100),
	(free_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x120)
};

bool Syscall_Init() {
	*syscalls.putchar = (putchar_syscall_ptr)&tty_putchar;
	*syscalls.puts = (puts_syscall_ptr)&tty_puts;
	*syscalls.printf = (printf_syscall_ptr)&tty_printf;
	*syscalls.getchar = (getchar_syscall_ptr)&tty_getchar;
	*syscalls.gets = (gets_syscall_ptr)&tty_gets;
	*syscalls.malloc = (malloc_syscall_ptr)&mem_alloc;
	*syscalls.free = (free_syscall_ptr)&mem_free;

	return true;
}
