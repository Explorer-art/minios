#include <kernel/tty.h>
#include <kernel/allocator.h>
#include <kernel/syscall.h>

Syscalls syscalls = {
	(putchar_syscall_ptr far*)0x00500250,
	(puts_syscall_ptr far*)0x00500270,
	(printf_syscall_ptr far*)0x00500290,
	(getchar_syscall_ptr far*)0x00500310,
	(gets_syscall_ptr far*)0x00500330,
	(malloc_syscall_ptr far*)0x00500350,
	(free_syscall_ptr far*)0x00500370
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
