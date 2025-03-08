bits 16

%define ENDL 0x0A, 0x0D

mov ax, cs         ; Устанавливаем сегмент данных (если программа в CS)
mov ds, ax

mov dx, msg_hello  ; Загружаем адрес строки в DX
call puts

ret

;
; Вывод строки на экран
;
; Параметры:
; - ds:dx: адрес начала строки
;

puts:
    push dx
    push ax
    push bx

    mov bx, dx      ; Копируем адрес строки в BX

.loop:
    mov al, [bx]    ; Загружаем байт из [DS:BX] в AL
    cmp al, 0       ; Если нулевой символ, завершаем вывод
    je .done
    mov ah, 0Eh     ; Функция BIOS для вывода символа в AL
    int 10h
    inc bx          ; Переход к следующему символу
    jmp .loop       ; Повторяем цикл

.done:
    pop bx
    pop ax
    pop dx

    ret

msg_hello db "Hello world from program!", ENDL, 0
