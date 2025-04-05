#pragma once

#include <stdint.h>

#define SYSCALL_VECTOR_BASE 0x20005000

typedef void (*putchar_syscall_ptr)(char c);
typedef char (*getchar_syscall_ptr);
typedef char* (*gets_syscall_ptr)(char* str);
typedef void* (*malloc_syscall_ptr)(uint32_t size);
typedef void (*free_syscall_ptr)(uint32_t* ptr);

typedef struct {
	putchar_syscall_ptr far* putchar;
	getchar_syscall_ptr far* getchar;
	gets_syscall_ptr far* gets;
	malloc_syscall_ptr far* malloc;
	free_syscall_ptr far* free;
} Syscalls;

bool Syscall_Init();
