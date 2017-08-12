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
		} else if (directive_name && label_name && is_valid_label(label_name, state->current_line_num, state->current_file_name)) {
			add_code_label(state, label_name);
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

int direc_data (state_t* state, char* label, char* contents) {
	char* ptr = contents;
	long num;

	if (label)
		add_data_label(state, label, ISNT_MATRIX);

	do {
		if (!EXPECT_NUMBER(num)) {
			return 0;
		}

		if (num < MIN_VALUE_SIGNED || num > MAX_VALUE_SIGNED) {
			fprintf(stderr, ERROR_DATA_OUT_OF_BOUNDS, num, state->current_line_num, state->current_file_name);
			return 0;
		}

		add_word(&state->data_table, &state->data_counter, (cpu_word)num);

		ptr = advance_whitespace(ptr);

		if (!MAYBE_CHAR(',')) {
			break;
		}

		ptr = advance_whitespace(ptr);
	} while (*ptr != '\0');

	EXPECT_EOL();

	return *ptr == '\0';
}

int direc_string (state_t* state, char* label, char* contents) {
	char* ptr = contents;
	char curr_char;

	if (label)
		add_data_label(state, label, ISNT_MATRIX);

	if (!EXPECT_CHAR('"')) {
		return 0;
	}
	while (EXPECT_ANY_CHAR(curr_char)) {
		if (curr_char == '"') {
			break;
		} else if (curr_char == '\0') {
			fprintf(stderr, ERROR_EXPECTED_CHARACTER_EOL, '"', state->current_line_num, state->current_file_name);
			state->failed = 1;
			return 0;
		} else {
			add_word(&state->data_table, &state->data_counter, curr_char);
		}
	}
	add_word(&state->data_table, &state->data_counter, 0);
	return 1;
}

int direc_mat (state_t* state, char* label, char* contents) {
	char* ptr = contents;
	long mat_x;
	long mat_y;
	int i;
	int zero_fill = 0;

	if (label)
		add_data_label(state, label, IS_MATRIX);

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
		fprintf(stderr, ERROR_MATRIX_DIMENSION_POSITIVE, mat_x < mat_y ? mat_x : mat_y, state->current_line_num, state->current_file_name);
		state->failed = 1;
		return 0;
	}

	// >> +1 << because declarations are one-indexed, but access is zero-indexed
	if (mat_x > MAX_VALUE_UNSIGNED+1 || mat_x < 0) {
		fprintf(stderr, ERROR_MATRIX_DIMENSION_OUT_OF_BOUNDS, mat_x, state->current_line_num, state->current_file_name);
		state->failed = 1;
		return 0;
	}
	if (mat_y > MAX_VALUE_UNSIGNED+1 || mat_y < 0) {
		fprintf(stderr, ERROR_MATRIX_DIMENSION_OUT_OF_BOUNDS, mat_y, state->current_line_num, state->current_file_name);
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

			add_word(&state->data_table, &state->data_counter, (cpu_word)value);
		} else {
			add_word(&state->data_table, &state->data_counter, 0);
		}
	}

	EXPECT_EOL();

	return 1;
}

int direc_entry (state_t* state, char* label, char* contents) {
	// TODO: Check if entry exists
	// TODO: Check if extern exists
	// TODO: Check if label exists

	if (contents == NULL || *advance_nonwhitespace(contents) != '\0')
		return 0;

	list_add_element(&state->entry_table, str_dup(contents));
	return 1;
}

int direc_extern (state_t* state, char* label, char* contents) {
	// TODO: Check if extern exists
	// TODO: Check if entry exists
	// TODO: Check if label exists

	if (contents == NULL || advance_whitespace(contents) == '\0')
		return 0;

	if (find_data_label(state, contents)) {
		fprintf(stderr, ERROR_LABEL_EXISTS, contents, state->current_line_num, state->current_file_name);
		state->failed = 1;
		return 0;
	}

	list_add_element(&state->extern_table, str_dup(contents));
	return 1;
}