#pragma once

#define PRINTF_STATE_NORMAL 0
#define PRINTF_STATE_LENGTH 1
#define PRINTF_STATE_LENGTH_SHORT 2
#define PRINTF_STATE_LENGTH_LONG 3
#define PRINTF_STATE_SPEC 4

#define PRINTF_LENGTH_DEFAULT 0
#define PRINTF_LENGTH_SHORT 1
#define PRINTF_LENGTH_SHORT_SHORT 2
#define PRINTF_LENGTH_LONG 3
#define PRINTF_LENGTH_LONG_LONG 4

#define BUFFER_SIZE 1024
#define ENTER 0x0D
#define SPACE 0x20
#define BACKSPACE 0x08
#define LEFT 0x25
#define UP 0x26
#define RIGHT 0x27
#define DOWN 0x28

void tty_clear();
void tty_putchar(char c);
void tty_puts(const char* str);
void tty_printf(const char* fmt, ...);
void tty_buffer_clear();
char tty_getchar();
char* tty_gets();
