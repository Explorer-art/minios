bits 16
org 0x25400

%define ENDL 0x0A, 0x0D

mov si, msg_hello
call print_string

ret

print_string:
    push ax
    xor ax, ax

.loop:
    lodsb
    cmp al, 0
    je .done
    push ax
    call [5000h]
    pop ax

    jmp .loop

.done:
    pop ax
    ret

msg_hello           db "Hello from userland!", ENDL, 0