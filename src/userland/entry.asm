bits 16

section _ENTRY class=CODE

extern _main
global entry

entry:
	call _main

	cli
	hlt