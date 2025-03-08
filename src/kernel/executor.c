#include <string.h>
#include <memory.h>
#include <kernel/tty.h>
#include <kernel/executor.h>
#include <kernel/fat.h>

uint8_t far* g_execute_code = (uint8_t far*)0x30000;

void execute(DISK disk, const char* filename) {
	char buffer[10240];
	uint8_t execute_code_offset = 0;

	FAT_File far* fd = FAT_Open(&disk, filename);
	uint32_t read_bytes = FAT_Read(&disk, fd, sizeof(buffer), g_execute_code);
	FAT_Close(fd);

	void (*entry)() = (void(*)())g_execute_code;
	entry();
}
