#include <stdint.h>
#include <kernel/tty.h>

void _cdecl kmain() {
	kernel_printf("Hello world!\n");

end:
	for(;;);
}
