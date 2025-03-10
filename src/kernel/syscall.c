#include <kernel/tty.h>
#include <kernel/allocator.h>
#include <kernel/syscall.h>

Syscalls syscalls = {
	(putchar_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x00),
	(puts_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x04),
	(printf_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x08),
	(getchar_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x0C),
	(gets_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x10),
	(malloc_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x14),
	(free_syscall_ptr far*)(SYSCALL_VECTOR_BASE + 0x18)
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
