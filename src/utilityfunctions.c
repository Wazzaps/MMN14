#include "utilityfunctions.h"

char string_get_last_char (char* string) {
	while (string[0] != '\0') string++;
	string--;
	return string[0];
}