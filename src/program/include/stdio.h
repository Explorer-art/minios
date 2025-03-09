#pragma once

typedef void (*putchar_syscall_ptr)(char c);
typedef void (*puts_syscall_ptr)(const char* str);
typedef void (*printf_syscall_ptr)(const char* fmt, ...);
typedef char (*getchar_syscall_ptr);
typedef char* (*gets_syscall_ptr)(char* str);

void putchar(char c);
void puts(const char* str);
void _cdecl printf(const char* fmt, ...);
char getchar();
char* gets(char* str);
