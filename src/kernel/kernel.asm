main:
	call clear_screen
	mov si, welcome_message
	call puts
	call in_char
	
	hlt

welcome_message: db "Hello World!", 0
