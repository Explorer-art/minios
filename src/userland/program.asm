bits 16
org 0x25400

%define ENDL 0x0A, 0x0D

start:
	mov si, msg_test
    mov ax, 15
    push ax
	call printf
    pop ax

	ret

%include 'lib/std.inc'

msg_test			db "Value: %d Aboba", ENDL, 0