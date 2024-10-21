#include "stdio.h"
#include "x86.h"

void write_char(char c) {
	x86_video_write_char(c, 0);
}

void putchar(const char* c) {
	write_char(*c);
}

void puts(const char* str) {
	while (*str) {
		putchar(str);
		str++;
	}
}