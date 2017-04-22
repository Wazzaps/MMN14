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
	unsigned int a_length = strlen(a);
	unsigned int b_length = strlen(b);
	char* output = malloc(a_length + b_length + 1);

	memcpy(output, a, a_length);
	memcpy(output + a_length, b, b_length + 1);

	return output;
}

char* string_copy (char* string) {
	unsigned int length = strlen(string);
	char* output = malloc(length + 1);
	memcpy(output, string, length);
	return output;
}

void string_append_char (char** string, char char_to_append) {
	string_expand_by(*string, 1);
	(*string)[strlen(*string)] = char_to_append;
}