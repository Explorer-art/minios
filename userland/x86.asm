bits 16

global _putchar

_putchar:
    push bp
    mov bp, sp

    push ax

    mov ax, 777h

    mov ax, [bp + 4]
    push ax
    call [5000h]
    pop ax

    pop ax

    mov sp, bp
    pop bp
    ret