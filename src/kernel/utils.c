#include <utils.h>
#include <string.h>
#include <memory.h>
#include <memdefs.h>

#define MAX_SIZE_ARG 1024

static char arg[MAX_SIZE_ARG];

uint32_t align(uint32_t number, uint32_t alignTo) {
    if (alignTo == 0)
        return number;

    uint32_t rem = number % alignTo;
    return (rem > 0) ? (number + alignTo - rem) : number;
}

char* string_split(char* str, char delim, int number) {
	int n = 0;

	for (int i = 0; i < strlen(str); i++) {
		if (str[i] != delim) {
			arg[i] = str[i];
		} else {
			if (n == number) {
				return arg;
			}

			memset(arg, '\0', MAX_SIZE_ARG);
			n++;
		}
	}

	return arg;
}
