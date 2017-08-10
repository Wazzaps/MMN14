#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parse_directives.h"
#include "constant_data.h"
#include "util_funcs.h"
#include "parsing.h"
#include "errors.h"

int find_directive (char*);

void parse_directives_and_labels (state_t* state) {
	char* line = malloc(LINE_LENGTH + 1);

	char* label_name = NULL;
	char* directive_name = NULL;
	char* code_contents = NULL;

	// Loop over every line
	while (get_line(line, LINE_LENGTH, state->current_file_ptr, state->current_line_num)) {
		state->current_line_num++;

		// Remove comment, and split label, directive/op and arguments/operands
		clean_and_split_line(line, &label_name, &directive_name, &code_contents, state, 1);

		// Check directive and label
		if (directive_name && ISDIRECTIVE(directive_name) &&
		    (!label_name || is_valid_label(label_name, state->current_line_num, state->current_file_name))) {
			int directive_id = find_directive(directive_name + 1);

			if (directive_id != -1) {
				// Execute the corresponding directive function
				if (!DIRECTIVES[directive_id].func(state, label_name, code_contents)) {
					state->failed = 1;
				}
			} else if (strlen(directive_name) == 1) {
				fprintf(stderr, ERROR_EMPTY_DIRECTIVE, state->current_line_num, state->current_file_name);
			} else {
				fprintf(stderr, ERROR_UNKNOWN_DIRECTIVE, directive_name, state->current_line_num, state->current_file_name);
			}
		}
	}

	// Return file pointer to beginning for op parser
	rewind(state->current_file_ptr);
}

int find_directive (char* directive_name) {
	int i;

	for (i = 0; i < DIRECTIVES_LENGTH; i++)
		if (!strcmp(directive_name, DIRECTIVES[i].name))
			return i;

	return -1;
}


////////////// Directives ////////////////

// NOTE: All labels need to be checked if they exist

// FIXME: What is this?
/*char* my_strchr (char* s, int c) {
	char* ret = NULL;

	if (*s == '\0') {
		return NULL;
	}

	ret = strchr(s, c);

	if (ret != NULL) {
		return ret;
	}

	return s + strlen(s);
}*/

int direc_data (state_t* state, char* label, char* contents) {
	char* ptr = contents;
	double num;

	// Add label to data labels table
	if (label != NULL) {
		data_label* new_label = malloc(sizeof(data_label)); //TODO : check allocting

		if (!new_label) {
			fprintf(stderr, ERROR_OUT_OF_MEMORY);
			exit(1);
		}

		new_label->name = label;
		new_label->data_address = state->data_counter;

		list_add_element(&state->data_labels_table, new_label);
	}

	char* endptr = ptr;
	while (*endptr != '\0') {
		// TODO: rewrite to use expect_number
		num = strtod(endptr, &endptr);

		if (endptr == NULL) {
			fprintf(stderr, ERROR_DATA_IS_NOT_NUM, state->current_line_num, state->current_file_name);
			return 0;
		}

		add_word(&state->data_table, &state->data_counter, (int) num);

		if (*endptr == '\0') {
			break;
		}

		endptr++;
	}

	if (endptr) {
		ptr = endptr;
	}

	if (*advance_whitespace(ptr) != '\0') {
		fprintf(stderr, ERROR_DATA_MISSING_COMMA, state->current_line_num, state->current_file_name);
		return 0;
	}

	return 1;
}

int direc_string (state_t* state, char* label, char* contents) {
	// TODO
	return 1;
}

int direc_mat (state_t* state, char* label, char* contents) {
	char* ptr = contents;
	long mat_x;
	long mat_y;
	int i;
	int zero_fill = 0;

	// Matrix size
	if (!EXPECT_CHAR('[')
	    || !EXPECT_NUMBER(mat_x)
	    || !EXPECT_CHAR(']')
	    || !EXPECT_CHAR('[')
	    || !EXPECT_NUMBER(mat_y)
	    || !EXPECT_CHAR(']')
	    || !EXPECT_SPACE_OR_EOL())
		return 0;

	if (mat_x <= 0 || mat_y <= 0) {
		fprintf(stderr, ERROR_MATRIX_DIMENSION_POSITIVE, state->current_line_num, state->current_file_name);
		state->failed = 1;
		return 0;
	}

	// >> +1 << because declarations are one-indexed, but access is zero-indexed
	if (mat_x > MAX_VALUE_UNSIGNED+1 || mat_x < 0 || mat_y > MAX_VALUE_UNSIGNED+1 || mat_y < 0) {
		fprintf(stderr, ERROR_MATRIX_DIMENSION_OUT_OF_BOUNDS, state->current_line_num, state->current_file_name);
		state->failed = 1;
		return 0;
	}

	// Initial data
	if (*ptr == '\0') {
		zero_fill = 1;
	}

	for (i = 0; i < mat_x * mat_y; i++) {
		if (!zero_fill) {
			long value;
			ptr = advance_whitespace(ptr);
			EXPECT_NUMBER(value);
			ptr = advance_whitespace(ptr);

			if (!MAYBE_CHAR(',')) {
				zero_fill = 1;
			}

			if (value > MAX_VALUE_SIGNED || value < MIN_VALUE_SIGNED) {
				fprintf(stderr, ERROR_DATA_OUT_OF_BOUNDS, value, state->current_line_num, state->current_file_name);
				state->failed = 1;
				return 0;
			}

			// TODO: Insert value
		} else {
			// TODO: Insert zero
		}
	}

	return 1;
}

int direc_entry (state_t* state, char* label, char* contents) {
	// TODO: Check if entry exists
	// TODO: Check if extern exists
	// TODO: Check if label exists
	if (contents == NULL || advance_nonwhitespace(contents) == '\0')
		return 0;
	list_add_element(&state->entry_table, contents);
	return 1;
}

int direc_extern (state_t* state, char* label, char* contents) {
	// TODO: Check if extern exists
	// TODO: Check if entry exists
	// TODO: Check if label exists
	if (contents == NULL || advance_nonwhitespace(contents) == '\0')
		return 0;
	list_add_element(&state->extern_table, contents);
	return 1;
}