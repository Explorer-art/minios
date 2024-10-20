clear_screen:
	push ax
	mov ah, 0x00
	mov al, 0x03
	int 10h
	pop ax
	ret

puts:
	push ax
	mov ah, 0x0e
	lodsb
	cmp al, 0
	je done
	int 10h

	jmp puts

done:
	pop ax
	ret
