#include <string.h>
#include <stdlib.h>
#include "whitespace.h"
#include "infinitestructures.h"

#define NEXT_CHAR(x) string_get_next_char(&x, &x##_counter)


infstring* whitespace_process (infstring* code) {
	infstring* output;
	output = _whitespace_firstpass(code);
	output = _whitespace_secondpass(output);
	output = _whitespace_thirdpass(output);

	return output;
}

/* First pass: Switch all \r\n to just \n by removing \r */
infstring* _whitespace_firstpass (infstring* code) {
	infstring* output = string_new();
	infstring* current = output;
	int code_counter = 0;
	unsigned int codelen = string_length(code);
	int i;

	/* Loop over every char */
	for (i = 0; i < codelen; i++) {
		char the_char = NEXT_CHAR(code);
		if (the_char != '\r') {
			current = string_append_to_last(current, the_char);
		}
	}

	return output;
}

/* Second pass: Remove all whitespace from starts of lines */
infstring* _whitespace_secondpass (infstring* code) {
	infstring* output = string_new();
	infstring* current = output;
	unsigned int codelen = string_length(code);
	int code_counter = 0;
	int i;
	int is_at_start = 1;

	/* Loop over every char */
	for (i = 0; i < codelen; i++) {
		char the_char = NEXT_CHAR(code);
		if (!is_at_start || (the_char != ' ' &&
		                     the_char != '\t' &&
                             the_char != '\n')) {
			current = string_append_to_last(current, the_char);
			is_at_start = 0;
		}
		if (the_char == '\n') {
			is_at_start = 1;
		}
	}

	return output;
}

/* Third pass: Remove all comments */
infstring* _whitespace_thirdpass (infstring* code) {
	infstring* output = string_new();
	infstring* current = output;
	unsigned int codelen = string_length(code);
	int code_counter = 0;
	int i;
	int is_in_comment = 0;
	int is_in_string = 0;

	/* Loop over every char */
	for (i = 0; i < codelen; i++) {
		char the_char = NEXT_CHAR(code);
		if (the_char == '\"' && !is_in_comment) {
			is_in_string = !is_in_string;
		}
		if (the_char == ';' && !is_in_string) {
			is_in_comment = 1;
		}
		if (the_char == '\n') {
			is_in_comment = 0;
			is_in_string = 0;
		}

		if (!is_in_comment) {
			current = string_append_to_last(current, the_char);
		}
	}

	return output;
}
