#include <kernel/panic.h>
#include <kernel/tty.h>
#include <kernel/x86.h>

void kpanic(const char* message) {
	uint16_t ax, bx, cx, dx, si, di, sp, bp;

	get_registers(&ax, &bx, &cx, &dx, &si, &di, &sp, &bp);

	kprintf("Registers:\n    AX: 0x%x\n    BX: 0x%x\n    CX: 0x%x\n    DX: 0x%x\n    SI: 0x%x\n    DI: 0x%x\n    SP: %x\n    BP: 0x%x\n\nKernel panic!\n", ax, bx, cx, dx, si, di, sp, bp);

	if (message == NULL) {
		kprintf("Reason: Unknown error\n");
	} else {
		kprintf("Reason: %s\n", message);
	}

	for (;;);
}
