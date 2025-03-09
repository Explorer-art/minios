	.file	"main.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
#APP
# 2 "src/program/main.c" 1
	mov ah, 0x0E 
mov al, 'A'  
mov bh, 0x00 
mov bl, 0x07 
int 0x10 
cli 
hlt 

# 0 "" 2
#NO_APP
	nop
	ud2
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 14.2.0-4ubuntu2) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
