bits 16
org 0x25400

%define ENDL 0x0A, 0x0D

jmp start

%include 'lib/stdio.inc'

start:
	push 'P'
	push f_msg
	call PRINTF
	ret

new_line	db 0x0A, 0x0D, 0
f_msg		db "You > '%c'", ENDL, 0