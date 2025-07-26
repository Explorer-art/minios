; ---------------------------------------------------
; The standard I/O library for Minios
;
; Author: Explorer-art (Truzme_)
; ---------------------------------------------------


;
; Put char
;
; Parameters:
; - ax: char
;

%define PUTCHAR [5000h]


;
; Puts
;
; Parameters:
; - ax: string ptr
;

%define PUTS [5004h]


;
; Printf
;
; Parameters:
; - ax: string ptr
; - stack: args
;

%define PRINTF [5008h]


;
; getchar
;
; Output:
; ax: get char
;

%define GETCHAR [500Ch]


;
; gets
;
; Output:
; ax: gets string ptr
;

%define GETS [5010h]