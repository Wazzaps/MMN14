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

	/* Loop over every line */
	while (get_line(line, LINE_LENGTH, state->current_file_ptr, state->current_line_num)) {
		state->current_line_num++;

		/* Remove comment, and split label, directive/op and arguments/operands */
		clean_and_split_line(line, &label_name, &directive_name, &code_contents, state, 1);

		/* Check directive and label */
		if (directive_name && ISDIRECTIVE(directive_name) &&
		    (!label_name || is_valid_label(label_name, state) || check_if_label_exists(state, label_name))) {
			int directive_id = find_directive(directive_name + 1);

			if (directive_id != -1) {
				/* Execute the corresponding directive function */
				if (!DIRECTIVES[directive_id].func(state, label_name, code_contents)) {
					state->failed = 1;
				}
			} else if (strlen(directive_name) == 1) {
				fprintf(stderr, ERROR_EMPTY_DIRECTIVE, state->current_line_num, state->current_file_name);
			} else {
				fprintf(stderr, ERROR_UNKNOWN_DIRECTIVE, directive_name, state->current_line_num, state->current_file_name);
			}
		} else if (directive_name && label_name && is_valid_label(label_name, state)) {
			add_code_label(state, label_name);
		}
	}

	/* Return file pointer to beginning for op parser */
	rewind(state->current_file_ptr);
	free(line);
}

int find_directive (char* directive_name) {
	int i;

	for (i = 0; i < DIRECTIVES_LENGTH; i++)
		if (!strcmp(directive_name, DIRECTIVES[i].name))
			return i;

	return -1;
}


/************* Directives ***************/

/*
 * Handles the .data directive
 * Returns 0 on fail, or 1 on success
 */
int direc_data (state_t* state, char* label, char* contents) {
	char* ptr = contents;
	long num;

	if (label)
		add_data_label(state, label);

	while (1) {
		if (!EXPECT_NUMBER(num)) {
			break;
		}

		if (num < MIN_VALUE_SIGNED_10bits || num > MAX_VALUE_SIGNED_10bits) {
			fprintf(stderr, ERROR_DATA_OUT_OF_BOUNDS, num, MIN_VALUE_SIGNED_10bits, MAX_VALUE_SIGNED_10bits,
			        state->current_line_num, state->current_file_name);
			return 0;
		}

		add_word(&state->data_table, &state->data_counter, (cpu_word) num);

		ptr = advance_whitespace(ptr);


		if (!MAYBE_CHAR(',')) {
			if (*ptr != '\0') {
				fprintf(stderr, ERROR_INVALID_CHARACTERS, ptr, state->current_line_num, state->current_file_name);
				return 0;
			} else
				break;
		}

		ptr = advance_whitespace(ptr);
	}

	EXPECT_EOL();

	return *ptr == '\0';
}

/*
 * Handles the .string directive
 * Returns 0 on fail, or 1 on success
 */
int direc_string (state_t* state, char* label, char* contents) {
	char* ptr = contents;
	char curr_char;

	if (label)
		add_data_label(state, label);

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

/*
 * Handles the .mat directive
 * Returns 0 on fail, or 1 on success
 */
int direc_mat (state_t* state, char* label, char* contents) {
	char* ptr = contents;
	long mat_x;
	long mat_y;
	int i;
	int zero_fill = 0;

	if (label)
		add_data_label(state, label);

	/* Matrix size */
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

	/* >> +1 << because declarations are one-indexed, but access is zero-indexed */
	if (mat_x > MAX_VALUE_UNSIGNED_10bits + 1 || mat_x < 0) {
		fprintf(stderr, ERROR_MATRIX_DIMENSION_OUT_OF_BOUNDS, mat_x, state->current_line_num, state->current_file_name);
		state->failed = 1;
		return 0;
	}
	if (mat_y > MAX_VALUE_UNSIGNED_10bits + 1 || mat_y < 0) {
		fprintf(stderr, ERROR_MATRIX_DIMENSION_OUT_OF_BOUNDS, mat_y, state->current_line_num, state->current_file_name);
		state->failed = 1;
		return 0;
	}

	/* Initial data */
	if (*ptr == '\0') {
		zero_fill = 1;
	}

	for (i = 0; i < mat_x * mat_y; i++) {
		if (!zero_fill) {
			long value;
			ptr = advance_whitespace(ptr);
			EXPECT_NUMBER(value);
			ptr = advance_whitespace(ptr);

			if (i == mat_x * mat_y - 1 || !MAYBE_CHAR(',')) {
				zero_fill = 1;
			}

			if (value > MAX_VALUE_SIGNED_10bits || value < MIN_VALUE_SIGNED_10bits) {
				fprintf(stderr, ERROR_DATA_OUT_OF_BOUNDS, value, MIN_VALUE_SIGNED_10bits, MAX_VALUE_SIGNED_10bits,
				        state->current_line_num, state->current_file_name);
				state->failed = 1;
				return 0;
			}

			add_word(&state->data_table, &state->data_counter, (cpu_word) value);
		} else {
			add_word(&state->data_table, &state->data_counter, 0);
		}
	}

	EXPECT_EOL();

	return 1;
}


/*
 * Handles the .entry directive
 * No label existance checking is done because the label may be defined later
 * We check label existance in main, after parsing.
 * Returns 0 on fail, or 1 on success
 */
int direc_entry (state_t* state, char* label, char* contents) {
	entry_with_line_num* new_element = calloc(1, sizeof(entry_with_line_num));

	if (!new_element) {
		fprintf(stderr, ERROR_OUT_OF_MEMORY);
		exit(1);
	}

	/* Check that label is valid */
	if (contents == NULL || *advance_nonwhitespace(contents) != '\0' || !is_valid_label(contents, state)) {
		return 0;
	}

	/* Add it */
	new_element->name = str_dup(contents);
	new_element->line_num = (unsigned) state->current_line_num;

	list_add_element(&state->entry_table, new_element);
	return 1;
}

/*
 * Handles the .extern directive
 * Returns 0 on fail, or 1 on success
 */
int direc_extern (state_t* state, char* label, char* contents) {
	/* Check that label is valid */
	if (contents == NULL || advance_whitespace(contents) == '\0' || !is_valid_label(contents, state)) {
		return 0;
	}

	/* Check if it already exists */
	if (find_data_label(state, contents) || is_extern_label(state, contents)) {
		fprintf(stderr, ERROR_LABEL_EXISTS, contents, state->current_line_num, state->current_file_name);
		return 0;
	}

	/* Add it */
	list_add_element(&state->extern_table, str_dup(contents));
	return 1;
}