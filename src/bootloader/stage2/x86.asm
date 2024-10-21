bits 16

section _TEXT class=CODE

global _x86_video_write_char

_x86_video_write_char:
	push bp
	mov bp, sp

	push bx

	mov ah, 0Eh
	mov al, [bp + 4]
	mov bh, [bp + 6]
	int 10h

	pop bx

	mov sp, bp
	pop bp
	ret