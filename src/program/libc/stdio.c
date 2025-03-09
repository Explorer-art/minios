#include <stdio.h>
#include <memdefs.h>

putchar_syscall_ptr far* putchar_syscall = (putchar_syscall_ptr far*)(0x00029000 + 0x00);
puts_syscall_ptr far* puts_syscall = (puts_syscall_ptr far*)(0x00029000 + 0x20);
printf_syscall_ptr far* printf_syscall = (printf_syscall_ptr far*)(0x00029000 + 0x40);
getchar_syscall_ptr far* getchar_syscall = (getchar_syscall_ptr far*)(0x00029000 + 0x60);
gets_syscall_ptr far* gets_syscall = (gets_syscall_ptr far*)(0x00029000 + 0x80);

void putchar(char c) {
	(*putchar_syscall)(c);
}

void puts(const char* str) {
	(*puts_syscall)(str);
}

void _cdecl printf(const char* fmt, ...) {
	(*printf_syscall)(fmt, (int*)&fmt);
}

char getchar() {
	return (*getchar_syscall);
}

char* gets(char* str) {
	str = (*gets_syscall);

	return str;
}
