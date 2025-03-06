#include <utils.h>
#include <string.h>
#include <memory.h>
#include <memdefs.h>
#include <kernel/tty.h>
#include <kernel/allocator.h>

uint32_t align(uint32_t number, uint32_t alignTo) {
    if (alignTo == 0)
        return number;

    uint32_t rem = number % alignTo;
    return (rem > 0) ? (number + alignTo - rem) : number;
}

int count_words(const char* str, char delim) {
	int count = 0;
	int in_word = 0;

	while (*str) {
		if (*str != delim && !in_word) {
			in_word = 1;
			count++;
		} else if (*str == delim) {
			in_word = 0;
		}

		str++;
	}

	return count;
}

char** string_split(char* str, char delim) {
	int word_count = count_words(str, delim);

	char** args = (char**) mem_alloc((word_count + 1) * sizeof(char *));

	if (args == NULL) {
		return NULL;
	}

	int word_index = 0;
	const char* word_start = NULL;

	while (*str) {
		if (*str != delim && word_start == NULL) {
			word_start = str;
		}

		if ((*str == delim || *(str + 1) == '\0') && word_start != NULL) {
			int word_length = str - word_start + ((*str == delim) ? 0 : 1);
			args[word_index] = (char*) mem_alloc(word_length + 1);

			if (args[word_index] == NULL) {
				for (int i = 0; i < word_index; i++) {
					mem_free((uint32_t*) args[i]);
				}

				mem_free((uint32_t*) args);
				return NULL;
			}

			memcpy(args[word_index], word_start, word_length);
			args[word_index][word_length] = '\0';

			word_index++;
			word_start = NULL;
		}

		str++;
	}

	args[word_count] = NULL;
	return args;
}

void free_split(char** args) {
	int i = 0;

	while (args[i] != NULL) {
		mem_free((uint32_t*) args[i]);
		i++;
	}

	mem_free((uint32_t*) args);
}

int get_args_count(char** args) {
	int count = 0;

	while (args[count] != NULL) {
		count++;
	}

	return count;
}
