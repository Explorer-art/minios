#include <stdlib.h>
#include <kernel/allocator.h>

void* malloc(uint32_t size) {
	return mem_alloc(size);
}

void free(uint32_t* ptr) {
	mem_free(ptr);
}
