bits 16

global _clear_screen
global _write_char
global _read_char

_clear_screen:
    push bp
    mov bp, sp

    push bx

    mov ah, 0h
    mov al, 3h
    int 10h

    pop bx

    mov sp, bp
    pop bp
    ret

_write_char:
    push bp
    mov bp, sp

    push ax
    push bx

    mov ah, 0Eh
    mov al, [bp + 4]
    mov bh, 0
    int 10h

    pop bx
    pop ax

    mov sp, bp
    pop bp
    ret

_read_char:
    push bp
    mov bp, sp

    push bx

    mov ah, 0h
    int 16h

    xor ah, ah

    pop bx

    mov sp, bp
    pop bp
    ret