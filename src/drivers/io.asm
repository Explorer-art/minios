putchar:
	mov al, [bx]
	int 10h
	ret

puts:
	mov ah, 0x0e
	call putchar
	inc bx

	cmp byte [bx], 0
	jnz puts
	ret
