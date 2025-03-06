#include <stdio.h>
#include <memdefs.h>

putchar_syscall_ptr far* putchar_syscall = (putchar_syscall_ptr far*)0x0055250;
puts_syscall_ptr far* puts_syscall = (puts_syscall_ptr far*)0x0055270;
printf_syscall_ptr far* printf_syscall = (printf_syscall_ptr far*)0x0055290;
getchar_syscall_ptr far* getchar_syscall = (getchar_syscall_ptr far*)0x0055310;
gets_syscall_ptr far* gets_syscall = (gets_syscall_ptr far*)0x0055330;

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
