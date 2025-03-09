bits 16

%define ENDL 0x0A, 0x0D

global entry

entry:
	ret


puts:
    push si
    push ax
    push bx

    mov ah, 0Eh

.loop:
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

msg_test db "TEST", ENDL, 0