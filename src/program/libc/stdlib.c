#include <stdlib.h>

malloc_syscall_ptr far* malloc_syscall = (malloc_syscall_ptr far*)(0x00029000 + 0x100);
free_syscall_ptr far* free_syscall = (free_syscall_ptr far*)(0x00029000 + 0x120);

void* malloc(uint32_t size) {
	return (*malloc_syscall)(size);
}

void free(uint32_t* ptr) {
	(*free_syscall)(ptr);
}
