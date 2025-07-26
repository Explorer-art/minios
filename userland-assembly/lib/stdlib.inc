; ---------------------------------------------------
; The standart library for Minios, which includes
; functions for working with memory
;
; Author: Exporer-art (Truzme_)
; ---------------------------------------------------


;
; Memory allocation
;
; Parameters:
; - stack: size
;
; Output:
; - ax: ptr
;

malloc:
	call [5008h]
	ret