#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infinitestructures.h"

char* string_expand_by (char* string, unsigned int length) {
	return realloc(string, strlen(string) + length + 1);
}

char* string_expand_to (char* string, unsigned int length) {
	return realloc(string, length + 1);
}

char* string_concat (char* a, char* b) {
	unsigned int aLength = strlen(a);
	unsigned int bLength = strlen(b);
	char* output = malloc(aLength + bLength + 1);

	memcpy(output, a, aLength);
	memcpy(output + aLength, b, bLength + 1);

	return output;
}

void string_append_char (char** string, char char_to_append) {
	string_expand_by(*string, 1);
	(*string)[strlen(*string)] = char_to_append;
}