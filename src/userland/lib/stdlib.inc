; ---------------------------------------------------
; The standard assembly library for Minios, which includes
; various functions for working with I/O, strings,
; memory, etc.
;
; Author: Truzme_
; ---------------------------------------------------


;
; Put char
;
; Parameters:
; - ax: char
;

putchar:
	push ax
	call [5000h]	; System call
	pop ax
	ret


;
; Puts
;
; Parameters:
; - si: string
;

puts:
	push ax
	xor ax, ax

.loop:
	lodsb
	cmp al, 0
	je .done
	call putchar
	jmp .loop

.done:
	pop ax
	ret


;
; Printf
;
; Parameters:
; - si: formatted string
; - stack: args
;


; 0x100 - 0
; 0x099 - arg
; 0x098 - 0
; 0x097 - ax
; 0x096 - 0
; 0x095 - si


printf:
    xor ax, ax

.loop:
    lodsb
    cmp al, 0
    je .done
    cmp al, '%'
    je .state_format
    call putchar
    jmp .loop

.state_format:
    lodsb
    cmp al, 0
    je .done
    cmp al, 'c'
    je .print_char
    cmp al, 's'
    je .print_string
    cmp al, 'd'
    je .print_dec
    cmp al, '%'
    call putchar
    jmp .loop

.print_char:
    push bp
    mov bp, sp
    mov ax, [bp + 4]
    call putchar
    pop bp
    jmp .loop

.print_string:
    push bp
    mov bp, sp
    push si
    mov si, [bp + 4]
    call puts
    pop si
    pop bp
    jmp .loop

.print_dec:
    push bp
    mov bp, sp
    mov ax, [bp + 4]
    push si
    push cx
    xor cx, cx
    lea si, [buffer]
    cmp ax, 0
    je .zero_case

.convert_loop:
    xor dx, dx
    div word [ten]
    add dl, '0'
    mov [si], dl
    inc si
    inc cx
    cmp ax, 0
    je .done_convert
    jmp .convert_loop

.zero_case:
    mov byte [si], '0'
    inc si

.done_convert:
    mov byte [si], 0
    dec si

.print_dec_loop:
    mov al, [si]
    call putchar
    dec si
    loop .print_dec_loop

    pop cx
    pop si
    pop bp
    jmp .loop

.done:
    ret


buffer			db 32
ten             dw 10