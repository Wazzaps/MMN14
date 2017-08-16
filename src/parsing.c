#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "errors.h"
#include "util_funcs.h"

int maybe_char (char c, char** ptr) {
	if (**ptr == c) {
		(*ptr)++;
		return 1;
	}
	return 0;
}

int expect_char (char c, char** ptr, state_t* state) {
	if (**ptr == c) {
		(*ptr)++;
		return 1;
	} else {
		if (**ptr == '\0')
			fprintf(stderr, ERROR_EXPECTED_CHARACTER_EOL, c, state->current_line_num, state->current_file_name);
		else
			fprintf(stderr, ERROR_EXPECTED_CHARACTER, c, **ptr, **ptr, state->current_line_num,
			        state->current_file_name);
		state->failed = 1;
		return 0;
	}
}

int expect_any_char (char* output, char** ptr, state_t* state) {
	if (**ptr != '\0')  {
		*output = **ptr;
		(*ptr)++;
		return 1;
	}
	fprintf(stderr, ERROR_EXPECTED_ANY_CHARACTER_EOL, state->current_line_num, state->current_file_name);
	state->failed = 1;
	return 0;
}

int maybe_number (long* output, char** ptr) {
	char* endptr;
	*output = strtol(*ptr, &endptr, 10);
	if (endptr != *ptr) {
		*ptr = endptr;
		return 1;
	}
	return 0;
}

int expect_number (long* output, char** ptr, state_t* state) {
	char* endptr;
	*output = strtol(*ptr, &endptr, 10);
	if (endptr != *ptr) {
		*ptr = endptr;
		return 1;
	} else {
		if (**ptr == '\0')
			fprintf(stderr, ERROR_EXPECTED_NUMBER_EOL, state->current_line_num, state->current_file_name);
		else
			fprintf(stderr, ERROR_EXPECTED_NUMBER, **ptr, **ptr, state->current_line_num, state->current_file_name);
		state->failed = 1;
		return 0;
	}
}

int expect_eol (char** ptr, state_t* state) {
	if (**ptr == '\0') {
		return 1;
	}
	fprintf(stderr, ERROR_EXPECTED_EOL, *ptr, state->current_line_num, state->current_file_name);
	state->failed = 1;
	return 0;
}

// Checks if the line ends or there's space, and advances whitespace if any.
int expect_whitespace_or_eol (char** ptr, state_t* state) {
	char* endptr;
	endptr = advance_whitespace(*ptr);
	if (endptr != *ptr) {
		*ptr = endptr;
		return 1;
	} else if (**ptr == '\0') {
		return 1;
	} else {
		fprintf(stderr, ERROR_EXPECTED_WHITESPACE, **ptr, **ptr, state->current_line_num, state->current_file_name);
		state->failed = 1;
		return 0;
	}
}