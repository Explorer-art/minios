#include <kernel/allocator.h>
#include <stdint.h>
#include <kernel/tty.h>

#define MEMORY_SIZE 16384
#define MEMORY_MAX_HANDLES 100

static uint8_t memory[MEMORY_SIZE] = {0};
static MemoryData memory_table[MEMORY_MAX_HANDLES];
static int count = 0;

bool check_range(uint32_t number, uint32_t range_start, uint32_t range_end) {
	if (number >= range_start && number <= range_end) {
		return true;
	}

	return false;
}

void print_memory_table() {
	for (int i = 0; i < count; i++) {
		kernel_printf("Index: %d\n", i);
	}
}

void* mem_alloc(uint32_t size) {
	if (size > MEMORY_SIZE || count >= MEMORY_MAX_HANDLES) {
		return NULL;
	}

	if (count == 0) {
		memory_table[count].StartAddr = &memory;
		memory_table[count].Size = size;
		count++;

		return memory_table[count - 1].StartAddr;
	}

	bool check;

	for (int index = 0; index < MEMORY_SIZE; index++) {
		check = true;
		uint32_t address = &memory[index];

		for (int i = 0; i < count; i++) {
			if (!check_range(address, memory_table[i].StartAddr, memory_table[i].StartAddr + memory_table[i].Size - 1)) {
				check = true;
			} else {
				check = false;
				break;
			}
		}

		if (check) {
			for (int i = 0; i < count; i++) {
				if (!check_range(address + size - 1, memory_table[i].StartAddr, memory_table[i].StartAddr + memory_table[i].Size - 1)) {
					check = true;
				} else {
					check = false;
					break;
				}
			}
		}

		if (check) {
			memory_table[count].StartAddr = address;
			memory_table[count].Size = size;
			count++;

			return memory_table[count - 1].StartAddr;
		}
	}

	return NULL;
}

void mem_free(uint32_t* ptr) {
	uint8_t memory_index = -1;

	for (int i = 0; i < count; i++) {
		if (memory_table[i].StartAddr == (uint32_t) ptr) {
			memory_index = i;
		}
	}

	if (memory_index == -1) {
		return;
	}

	for (int i = memory_index; i < count - 1; i++) {
		memory_table[i] = memory_table[i + 1];
	}

	count--;
}
