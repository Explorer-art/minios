bits 16
org 0x27000

%define ENDL 0x0A, 0x0D

mov ax, msg_hello
push ax

call [5004h]

ret

msg_hello           db "Hello from program!", ENDL, 0
