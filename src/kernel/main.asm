bits 16
org 0x0

%define ENDL 0Ah, 0Dh

;
; MAIN
;

main:
	mov si, msg_hello
	call puts

.halt:
	cli
	hlt



;
; Вывод строки на экран
;
; Параметры:
; - ds:si: адрес начала строки
;

puts:
	push si
	push ax

.loop:
	mov ah, 0x0e
	lodsb
	cmp al, 0
	je .done
	int 10h

	jmp .loop

.done:
	pop ax
	pop si
	ret



msg_hello:		db "Hello world from KERNEL!", ENDL, 0