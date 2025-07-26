#pragma once

#include <stdint.h>
#include <kernel/fat.h>

#define SYSCALL_VECTOR_BASE 0x20005000

typedef void (*putchar_syscall_ptr)(char c);
typedef void (*tty_puts_syscall_ptr)(const char* str);
typedef void (*kprintf_syscall_ptr)(const char* fmt, ...);
typedef char (*getchar_syscall_ptr);
typedef char* (*gets_syscall_ptr)(char* str);
typedef void* (*malloc_syscall_ptr)(uint32_t size);
typedef void (*free_syscall_ptr)(uint32_t* ptr);
typedef FAT_File far* (*fat_open_syscall_ptr)(const char* path);
typedef uint32_t (*fat_read_syscall_ptr)(FAT_File far* file, uint32_t byte_count, void* data_out);
typedef void (*fat_close_syscall_ptr)(FAT_File far* file);

typedef struct {
	putchar_syscall_ptr far* putchar;
	tty_puts_syscall_ptr far* puts;
	kprintf_syscall_ptr far* printf;
	getchar_syscall_ptr far* getchar;
	gets_syscall_ptr far* gets;
	malloc_syscall_ptr far* malloc;
	free_syscall_ptr far* free;
	fat_open_syscall_ptr far* fat_open;
	fat_read_syscall_ptr far* fat_read;
	fat_close_syscall_ptr far* fat_close;
} Syscalls;

bool Syscall_Init();
