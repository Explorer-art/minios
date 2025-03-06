#include <stdint.h>
#include <memory.h>
#include <kernel/tty.h>
#include <kernel/x86.h>

static char buffer[BUFFER_SIZE];
const char HexChars[] = "0123456789abcdef";

void tty_clear() {
	clear_screen();
}

void tty_putchar(char c) {
	write_char(c);
}

void tty_puts(const char* str) {
	while (*str) {
		tty_putchar(*str);

		if (*str == '\n') {
			tty_putchar('\r');
		}
		
		str++;
	}
}

void puts_f(const char far* str) {
	while (*str) {
		tty_putchar(*str);
		str++;
	}
}

int* printf_number(int* argp, int length, bool sign, int radix)
{
    char buffer[32];
    unsigned long long number;
    int number_sign = 1;
    int pos = 0;

    // process length
    switch (length)
    {
        case PRINTF_LENGTH_SHORT_SHORT:
        case PRINTF_LENGTH_SHORT:
        case PRINTF_LENGTH_DEFAULT:
            if (sign)
            {
                int n = *argp;
                if (n < 0)
                {
                    n = -n;
                    number_sign = -1;
                }
                number = (unsigned long long)n;
            }
            else
            {
                number = *(unsigned int*)argp;
            }
            argp++;
            break;

        case PRINTF_LENGTH_LONG:
            if (sign)
            {
                long int n = *(long int*)argp;
                if (n < 0)
                {
                    n = -n;
                    number_sign = -1;
                }
                number = (unsigned long long)n;
            }
            else
            {
                number = *(unsigned long int*)argp;
            }
            argp += 2;
            break;

        case PRINTF_LENGTH_LONG_LONG:
            if (sign)
            {
                long long int n = *(long long int*)argp;
                if (n < 0)
                {
                    n = -n;
                    number_sign = -1;
                }
                number = (unsigned long long)n;
            }
            else
            {
                number = *(unsigned long long int*)argp;
            }
            argp += 4;
            break;
    }

    // convert number to ASCII
    do 
    {
        uint32_t rem;
        div64_32(number, radix, &number, &rem);
        buffer[pos++] = HexChars[rem];
    } while (number > 0);

    // add sign
    if (sign && number_sign < 0)
        buffer[pos++] = '-';

    // print number in reverse order
    while (--pos >= 0)
        tty_putchar(buffer[pos]);

    return argp;
}

void tty_printf(const char* fmt, ...) {
	int* argp = (int*)&fmt;
	int state = PRINTF_STATE_NORMAL;
	int length = PRINTF_LENGTH_DEFAULT;
	int radix = 10;
	bool sign = true;

	argp++;

	while (*fmt) {
		switch (state) {
			case PRINTF_STATE_NORMAL:
				switch (*fmt) {
				case '%':
					state = PRINTF_STATE_LENGTH;
					break;
				case '\n':
					tty_putchar('\n');
					tty_putchar('\r');
					break;
				default:
					tty_putchar(*fmt);
					break;
				}
				break;
			case PRINTF_STATE_LENGTH:
				switch (*fmt) {
					case 'h':
						state = PRINTF_STATE_LENGTH_SHORT;
						length = PRINTF_LENGTH_SHORT;
						break;
					case 'l':
						state = PRINTF_STATE_LENGTH_LONG;
						length = PRINTF_LENGTH_LONG;
						break;
					default:
						goto PRINTF_STATE_SPEC_;
				}
				break;
			case PRINTF_STATE_LENGTH_SHORT:
				if (*fmt == 'h') {
					state = PRINTF_STATE_SPEC;
					length = PRINTF_LENGTH_SHORT_SHORT;
				} else {
					goto PRINTF_STATE_SPEC_;
				}
			case PRINTF_STATE_LENGTH_LONG:
				if (*fmt == 'l') {
					state = PRINTF_STATE_SPEC;
					length = PRINTF_LENGTH_LONG_LONG;
				} else {
					goto PRINTF_STATE_SPEC_;
				}
			case PRINTF_STATE_SPEC:
				PRINTF_STATE_SPEC_:
				switch (*fmt) {
					case 'c':
						tty_putchar((char)*argp);
						argp++;
						break;
					case 's':
						if (length == PRINTF_LENGTH_LONG || length == PRINTF_LENGTH_LONG_LONG) {
							puts_f(*(const char far**)argp);
							argp++;
							break;
						} else {
							tty_puts(*(const char**)argp);
							argp++;
							break;
						}
					case '%':
						tty_putchar('%');
						break;
					case 'd':
					case 'i':
						radix = 10;
						sign = true;
						argp = printf_number(argp, length, sign, radix);
						break;
					case 'u':
						radix = 10;
						sign = false;
						argp = printf_number(argp, length, sign, radix);
						break;
					case 'X':
					case 'x':
					case 'p':
						radix = 16;
						sign = false;
						argp = printf_number(argp, length, sign, radix);
						break;
					case 'o':
						radix = 8;
						sign = false;
						argp = printf_number(argp, length, sign, radix);
						break;
					default:
						break;
				}

				state = PRINTF_STATE_NORMAL;
				length = PRINTF_LENGTH_DEFAULT;
				break;
		}

		fmt++;
	}
}

void tty_buffer_clear() {
	memset(buffer, '\0', BUFFER_SIZE);
}

char tty_getchar() {
	return read_char();
}

char* tty_gets() {
	int i = 0;
	char c;

	tty_buffer_clear();

	while (true) {
		c = tty_getchar();

		if (c == ENTER || i >= BUFFER_SIZE) {
			tty_putchar('\n');
			tty_putchar('\r');
			break;
		} else if (c == BACKSPACE) {
			if (i > 0) {
				tty_putchar(BACKSPACE);
				tty_putchar(SPACE);
				tty_putchar(BACKSPACE);
				i--;
				buffer[i] = '\0';
			}
		} else {
			write_char(c);
			buffer[i] = c;
			i++;
		}
	}

	return buffer;
}
