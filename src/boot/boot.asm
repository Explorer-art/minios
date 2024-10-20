org 0x7c00
bits 16

boot:
	cli ; Отключаем прерывания

	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7c00

	; Чтение ядра с диска
	mov ah, 0x02
	mov al, 0x01 ; Количество секторов на чтение
	mov ch, 0x00 ; Номер дорожки
	mov cl, 0x02 ; Номер начального сектора
	mov dh, 0x00 ; Номер головки
	mov dl, 0x80 ; Номер устройства
	mov bx, 0x7e00
	int 13h

	jc read_error

	jmp 0x7e00

read_error:
	mov bx, read_error_message
	call puts

	jmp $

read_error_message: db "Read error!", 0

times 510 - ($-$$) db 0
dw 0xaa55

jmp main

%include "src/kernel/kernel.asm"

%include "src/drivers/io.asm"
