bits 16

%define ENDL 0x0A, 0x0D

mov ah, 0Eh
mov al, 'H'
int 10h

mov ah, 0Eh
mov al, 'e'
int 10h

mov ah, 0Eh
mov al, 'l'
int 10h

mov ah, 0Eh
mov al, 'l'
int 10h

mov ah, 0Eh
mov al, 'o'
int 10h

mov ah, 0Eh
mov al, ' '
int 10h

mov ah, 0Eh
mov al, 'w'
int 10h

mov ah, 0Eh
mov al, 'o'
int 10h

mov ah, 0Eh
mov al, 'r'
int 10h

mov ah, 0Eh
mov al, 'l'
int 10h

mov ah, 0Eh
mov al, 'd'
int 10h

mov ah, 0Eh
mov al, '!'
int 10h

mov ah, 0Eh
mov al, 0Ah
int 10h

mov ah, 0Eh
mov al, 0Dh
int 10h

ret

;
; Вывод строки на экран
;
; Параметры:
; - ds:si: адрес начала строки
;

puts:
    push si
    push ax
    push bx

.loop:
    mov ah, 0Eh
    mov bh, 0
    lodsb
    cmp al, 0
    je .done
    int 10h

    jmp .loop

.done:
    pop bx
    pop ax
    pop si
    ret

msg_hello		db "Hello world from program!", ENDL, 0