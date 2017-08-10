#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "util_funcs.h"
#include "constant_data.h"
#include "errors.h"

/* Adds an extension to a filename */
char* file_add_extension(char* original, char* extension) {
	size_t len = strlen(original);
	size_t extlen = strlen(extension) + 1;
	char* output = malloc(len + 1 + extlen + 1); // filename, '.', extension, '\0'

	strcpy(output, original);
	output[len] = '.';
	strcpy(output + len + 1, extension);

	return output;
}

/* Gets a line from a file stream, until a length is
 * reached, then skip to next line. */
int get_line (char* buffer, int length, FILE* stream, int line_num) {
	int last_char = fgetc(stream);
	int input_length = 0;
	int reached_end = 0;
	int did_max_out = 0;

	while (last_char != EOF && last_char != '\n') {
		/* Slide to end of line if reached end of buffer */
		if (input_length == length) {
			if (reached_end) {
				did_max_out = 1;
				last_char = fgetc(stream);
				continue;
			}
			reached_end = 1;
		}
		buffer[input_length++] = (char) last_char;
		last_char = fgetc(stream);
	}

	buffer[input_length] = '\0';

	if (did_max_out)
		fprintf(stderr, ERROR_LINE_TOO_LONG, line_num+1, length);

	return last_char != EOF || input_length != 0;
}

void remove_comment (char* line) {
	int i;
	int is_in_string = 0;

	for (i = 0; i < LINE_LENGTH && line[i] != '\0'; i++) {
		if (line[i] == '"') {
			is_in_string = !is_in_string;
		} else if (line[i] == ';' && !is_in_string) {
			line[i] = '\0';
			break;
		}
	}
}

/* Returns a pointer to the first non whitespace character in a string */
char* advance_whitespace (char* str) {
	if (str == NULL) return NULL;
	while (isblank(*str)) str++;
	return str;
}

/* Returns a pointer to the first non whitespace character in a string */
char* advance_nonwhitespace (char* str) {
	if (str == NULL) return NULL;
	while (!isblank(*str) && *str != '\0') str++;
	return str;
}

/* Replaces the first whitespace character in the
 * last whitespace block of a string with \0 */
char* block_whitespace (char* str) {
	if (str == NULL) return NULL;
	char* end = str + strlen(str) - 1;
	while (isblank(*end) && end != str) end--;
	if (end != str && end != str + strlen(str)) {
		*(end + 1) = '\0';
	}
	return str;
}

char* split_label_and_code (char* line) {
	int i;
	int is_in_string = 0;

	for (i = 0; i < LINE_LENGTH && line[i] != '\0'; i++) {
		if (line[i] == '"') {
			is_in_string = !is_in_string;
		} else if (line[i] == ':' && !is_in_string) {
			line[i] = '\0';
			return line + i + 1;
		}
	}

	return NULL;
}

// Remove comment, and split label, directive/op and arguments/operands
void clean_and_split_line (char* line, char** _label_name, char** _name, char** _code_contents, state_t* state, int show_errors) {
	char* start_of_line = NULL;

	/* Replace `;` with `\0` so the comment is ignored */
	remove_comment(line);

	/* Trim whitespace from end */
	start_of_line = block_whitespace(line);

	/* Search for a colon, if found then split line into label
	 * ("label_name") and code ("code_contents") and skip whitespace */
	*_name = advance_whitespace(split_label_and_code(start_of_line));

	if (*_name == NULL) { /* No colon found */
		*_name = advance_whitespace(start_of_line);
		*_label_name = NULL;

		/* Nothing found */
		if (**_name == '\0') {
			*_name = NULL;
			*_code_contents = NULL;
			return;
		}
	} else if (strlen(advance_whitespace(start_of_line)) == 0) {  /* Label is empty */
		*_label_name = NULL;
		if (show_errors)
			fprintf(stderr, ERROR_EMPTY_LABEL, state->current_line_num, state->current_file_name);
	} else if (**_name == '\0') { /* Label isn't empty, code is empty */
		if (show_errors)
			fprintf(stderr, ERROR_USELESS_LABEL, block_whitespace(advance_whitespace(start_of_line)), state->current_line_num, state->current_file_name);
		*_label_name = NULL;
		*_name = NULL;
		*_code_contents = NULL;
		return;
	} else { /* Label isn't empty */
		int failed = 0;
		*_label_name = start_of_line;

		if (isspace(**_label_name)) {
			if (show_errors)
				fprintf(stderr, ERROR_LABEL_NOT_ON_START_OF_LINE, state->current_line_num, state->current_file_name);
			failed = 1;
		}
		if (isspace(*(*_label_name + strlen(*_label_name) - 1))) {
			if (show_errors)
				fprintf(stderr, ERROR_WHITESPACE_AFTER_LABEL, state->current_line_num, state->current_file_name);
			failed = 1;
		}
		*_label_name = failed ? NULL : block_whitespace(advance_whitespace(*_label_name));

	}

	// Search for first whitespace
	*_code_contents = advance_nonwhitespace(*_name);

	// Block it
	if (**_code_contents == '\0')
		return;
	**_code_contents = '\0';

	// Skip it
	*_code_contents = advance_whitespace(*_code_contents + 1);

}

/* Gets a label and tells if it's valid (not a register or a reserved word) */
int is_valid_label(char *name, int line_num, char *file_name) {
	int i;
	size_t name_length = strlen(name);
	char* name_lowercase = malloc(name_length+1);
	long register_test;
	char* end_ptr;

	// Labels can't start with a number
    if (!isalpha(name[0])) {
        fprintf(stderr, ERROR_LABEL_CANNOT_START_WITH_NUM, line_num, file_name);
		return 0;
	}


	// Labels can't be equal to op names or assembly directive names, in any case
	for (i = 0; i < name_length; i++) {
        if (!isalnum(name[i])) {
            fprintf(stderr, ERROR_LABEL_NAME_NOT_LETTER_OR_NUM, line_num, file_name);
            return 0;
        }
		name_lowercase[i] = (char)tolower(name[i]);

	}
	for (i = 0; i < OPS_LENGTH; i++) {
		if (!strcmp(OPS[i].name, name_lowercase)) {
            fprintf(stderr, ERROR_LABEL_NAME_IDENTICAL_OP_NAME, line_num, file_name);
			return 0;
		}

	}
	for (i = 0; i < DIRECTIVES_LENGTH; i++) {
		if (!strcmp(DIRECTIVES[i].name, name_lowercase)) {
            fprintf(stderr, ERROR_LABEL_NAME_IDENTICAL_DIR_MAME, line_num, file_name);
			return 0;
		}
	}

	// Labels can't be register names
	if (name_lowercase[0] == 'r') {
		register_test = strtol(name_lowercase+1, &end_ptr, 10);
		if ((end_ptr != name_lowercase + 1) && (*end_ptr == '\0') && (register_test >= MINIMUM_REG) && (register_test <= MAXIMUM_REG)) {
            fprintf(stderr, ERROR_LABEL_NAME_IDENTICAL_REG_MAME, line_num, file_name);
			return 0;
		}
	}

	return 1;
}