bits 16

section _ENTRY class=CODE

extern _kmain
global entry

entry:
	cli
	mov ax, ds
	mov ss, ax
	mov sp, 0
	mov bp, sp
	sti

	call _kmain

	cli
	hlt
