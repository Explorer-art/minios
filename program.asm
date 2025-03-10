bits 16
org 0x27000

%define ENDL 0x0A, 0x0D

mov si, msg_hello
call puts

call [8000h]

ret

puts:
    push si
    push ax
    push bx

    mov ah, 0Eh
    mov bh, 0

.loop:
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

msg_hello db "Hello from program!", ENDL, 0
