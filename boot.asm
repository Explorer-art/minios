[bits 16]
org 0x7C00

start:
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 7C00h

	; switch to protected mode
	cli
	call EnableA20
	call LoadGDT

	mov eax, cr0
	or al, 1
	mov cr0, eax

	jmp 08h:.pmode

.pmode:
	jmp .pmode

EnableA20:
	[bits 16]

	;disable keyboard
	call A20WaitInput
	mov al, KbdControllerDisableKeyboard
	out KbdControllerCommandPort, al

	; read control output port
	call A20WaitInput
	mov al, KbdControllerReadCtrlOutputPort
	out KbdControllerCommandPort, al

	call A20WaitOutput
	in al, KbdControllerDataPort
	push eax

	; write control output port
	call A20WaitInput
	mov al, KbdControllerWriteCtrlOutputPort
	out KbdControllerCommandPort, al
    
	call A20WaitInput
	pop eax
	or al, 2                                    ; bit 2 = A20 bit
	out KbdControllerDataPort, al

	; enable keyboard
	call A20WaitInput
	mov al, KbdControllerEnableKeyboard
	out KbdControllerCommandPort, al

	call A20WaitInput
	ret

LoadGDT:
	[bits 16]

	lgdt [g_GDTDesc]
	ret

A20WaitInput:
	[bits 16]

	in al, KbdControllerCommandPort
	test al, 2
	jnz A20WaitInput
	ret

A20WaitOutput:
	[bits 16]

	in al, KbdControllerCommandPort
	test al, 1
	jz A20WaitOutput
	ret

KbdControllerDataPort				equ 0x60
KbdControllerCommandPort			equ 0x64
KbdControllerEnableKeyboard			equ 0xAE
KbdControllerDisableKeyboard		equ 0xAD
KbdControllerReadCtrlOutputPort		equ 0xD0
KbdControllerWriteCtrlOutputPort	equ 0xD1

g_GDT:		; NULL descriptor
			dq 0

			; 32-bit code segment
			dw 0FFFFh                   ; limit (bits 0-15) = 0xFFFFF for full 32-bit range
			dw 0                        ; base (bits 0-15) = 0x0
			db 0                        ; base (bits 16-23)
			db 10011010b                ; access (present, ring 0, code segment, executable, direction 0, readable)
			db 11001111b                ; granularity (4k pages, 32-bit pmode) + limit (bits 16-19)
			db 0                        ; base high

			; 32-bit data segment
			dw 0FFFFh                   ; limit (bits 0-15) = 0xFFFFF for full 32-bit range
			dw 0                        ; base (bits 0-15) = 0x0
			db 0                        ; base (bits 16-23)
			db 10010010b                ; access (present, ring 0, data segment, executable, direction 0, writable)
			db 11001111b                ; granularity (4k pages, 32-bit pmode) + limit (bits 16-19)
			db 0                        ; base high

			; 16-bit code segment
			dw 0FFFFh                   ; limit (bits 0-15) = 0xFFFFF
			dw 0                        ; base (bits 0-15) = 0x0
			db 0                        ; base (bits 16-23)
			db 10011010b                ; access (present, ring 0, code segment, executable, direction 0, readable)
			db 00001111b                ; granularity (1b pages, 16-bit pmode) + limit (bits 16-19)
			db 0                        ; base high

			; 16-bit data segment
			dw 0FFFFh                   ; limit (bits 0-15) = 0xFFFFF
			dw 0                        ; base (bits 0-15) = 0x0
			db 0                        ; base (bits 16-23)
			db 10010010b                ; access (present, ring 0, data segment, executable, direction 0, writable)
			db 00001111b                ; granularity (1b pages, 16-bit pmode) + limit (bits 16-19)
			db 0                        ; base high

g_GDTDesc:
			dw g_GDTDesc - g_GDT - 1
			dd g_GDT

times 510 - ($-$$) db 0
dw 0xAA55