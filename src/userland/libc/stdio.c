#include <stdio.h>
#include <memdefs.h>

putchar_syscall_ptr far* putchar_syscall = (putchar_syscall_ptr far*)0x00500250;
puts_syscall_ptr far* puts_syscall = (puts_syscall_ptr far*)0x00500270;
printf_syscall_ptr far* printf_syscall = (printf_syscall_ptr far*)0x00500290;
getchar_syscall_ptr far* getchar_syscall = (getchar_syscall_ptr far*)0x00500310;
gets_syscall_ptr far* gets_syscall = (gets_syscall_ptr far*)0x00500330;

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
