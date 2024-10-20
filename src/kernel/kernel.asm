main:
	mov bx, hello_message
	call puts

	jmp $

hello_message: db "Hello World!", 0
