bits 16

section _TEXT class=CODE

global _x86_div64_32
global _x86_video_write_char

_x86_div64_32:

    ; make new call frame
    push bp             ; save old call frame
    mov bp, sp          ; initialize new call frame

    push bx

    ; divide upper 32 bits
    mov eax, [bp + 8]   ; eax <- upper 32 bits of dividend
    mov ecx, [bp + 12]  ; ecx <- divisor
    xor edx, edx
    div ecx             ; eax - quot, edx - remainder

    ; store upper 32 bits of quotient
    mov bx, [bp + 16]
    mov [bx + 4], eax

    ; divide lower 32 bits
    mov eax, [bp + 4]   ; eax <- lower 32 bits of dividend
                        ; edx <- old remainder
    div ecx

    ; store results
    mov [bx], eax
    mov bx, [bp + 18]
    mov [bx], edx

    pop bx

    ; restore old call frame
    mov sp, bp
    pop bp
    ret

_x86_video_write_char:
	push bp
	mov bp, sp

	push bx

	mov ah, 0Eh
	mov al, [bp + 4]
	mov bh, [bp + 6]
	int 10h

	pop bx

	mov sp, bp
	pop bp
	ret