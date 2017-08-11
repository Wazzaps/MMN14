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
void add_label(state_t *state, char *label) {
	data_label *new_label = malloc(sizeof(data_label)); //TODO : check allocating
	if (new_label == NULL) {
		fprintf(stderr, ERROR_OUT_OF_MEMORY);
		exit(1);
	}
	new_label->name = label;
	new_label->data_address = state->data_counter;

	list_add_element(&state->data_labels_table, new_label);
}

int direc_data(state_t *state, char *label, char *contents) {
	char *ptr = contents;
	double num;
	char *endptr = ptr;

	if (label != NULL) {
		add_label(state, label);
	}

    while (*endptr != '\0') {
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
	char *ptr = contents;
	int i = 1;

	if (label != NULL) {
		add_label(state, label);
	}

	if (!EXPECT_CHAR('\"')) {
		fprintf(stderr, ERROR_INVALID_STRING_CONTENT, state->current_line_num, state->current_file_name);
		return 0;
	}

	for (i; i <= strlen(ptr) - 2; i++) {
		add_word(&state->data_table, &state->data_counter, (ptr[i] - '0') + ASCII_ZERO);
	}
	add_word(&state->data_table, &state->data_counter, 0);
	return 1;
}

int direc_mat (state_t* state, char* label, char* contents) {
	char* ptr = contents;
	char *endptr;
	long mat_x;
	long mat_y;
	int i;
	int zero_fill = 0;
	double num;

	if (label != NULL) {
		add_label(state, label);
	}

	// Matrix size
	if (!EXPECT_CHAR('[')
	    || !EXPECT_NUMBER(mat_x)
	    || !EXPECT_CHAR(']')
	    || !EXPECT_CHAR('[')
	    || !EXPECT_NUMBER(mat_y)
	    || !EXPECT_CHAR(']')
	    || !EXPECT_SPACE_OR_EOL())
		return 0;

	// Initial data
	if (*ptr == '\0') {
		zero_fill = 1;
	}

	endptr = ptr;
	for (i = 0; i < mat_x * mat_y; i++) {
		if ((!zero_fill) || (*endptr == '0')) {
			/*			long value;
                       ptr = advance_whitespace(ptr);
                       EXPECT_NUMBER(value);
                       ptr = advance_whitespace(ptr);

                       if (!MAYBE_CHAR(',')) {
                           zero_fill = 1;
                       }

                       if (value <= 0) {
                           fprintf(stderr, ERROR_MATRIX_DIMENSION_POSITIVE, state->current_line_num, state->current_file_name);
                           state->failed = 1;
                           return 0;
                       } */

			num = strtod(endptr, &endptr);
			if (endptr == NULL) {
				fprintf(stderr, ERROR_MAT_DATA_IS_NOT_NUM, state->current_line_num, state->current_file_name);
				return 0;
			}
			fprintf(stdout, "Got matrix number :\t%d\n", (int) num);
			add_word(&state->data_table, &state->data_counter, (int) num);

			if (*endptr == '\0') {
				break;
			}

			endptr++;

		} else {
			add_word(&state->data_table, &state->data_counter, 0);
		}
	}
	if (endptr) {
		ptr = endptr;
	}

	if (*advance_whitespace(ptr) != '\0') {
		fprintf(stderr, ERROR_MAT_DATA_MISSING_COMMA, state->current_line_num, state->current_file_name);
		return 0;
	}
	return 1;
}

int direc_entry (state_t* state, char* label, char* contents) {
/*	list *name = state->entry_table;
	while ( name != NULL ) {
		if ( !strcmp(label, (char *)(name->data) )) {
			fprintf(stderr, ERROR_REPEAT_ENTRY_LABEL, state->current_line_num, state->current_file_name);
			return 0;
		}
		if ( name->next != NULL) {
			break;
		}
		else {
			name = name->next;
		}
	}
	if ( !is_valid_label(label,state->current_line_num, state->current_file_name) ) {
		return 0;
	}

	if (contents == NULL || advance_nonwhitespace(contents) == '\0')
		return 0;
	list_add_element(&state->entry_table, contents); */
	return 1;
}

int direc_extern (state_t* state, char* label, char* contents) {
/*	list *name = state->extern_table;
	while (name->next != NULL) {
		if ( !strcmp(label, (char *)(name->data) ) ){
			fprintf(stderr, ERROR_REPEAT_EXTERN_LABEL, state->current_line_num, state->current_file_name);
			return 0;
		}
	}
	if ( !is_valid_label(label,state->current_line_num, state->current_file_name) ) {
		return 0;
	}
	if (contents == NULL || advance_nonwhitespace(contents) == '\0')
		return 0;
	list_add_element(&state->extern_table, contents);*/
	return 1;
}