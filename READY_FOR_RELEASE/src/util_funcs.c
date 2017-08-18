#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "util_funcs.h"
#include "constant_data.h"
#include "errors.h"

/* Adds an extension to a filename */
char* file_add_extension (char* original, char* extension) {
	size_t len = strlen(original);
	size_t extlen = strlen(extension) + 1;
	char* output = malloc(len + 1 + extlen + 1); /* filename, '.', extension, '\0' */

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
			}
			reached_end = 1;
			last_char = fgetc(stream);
			continue;
		}
		buffer[input_length++] = (char) last_char;
		last_char = fgetc(stream);
	}

	buffer[input_length] = '\0';

	if (did_max_out)
		fprintf(stderr, ERROR_LINE_TOO_LONG, line_num + 1, length);

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
	while (isspace(*str)) str++;
	return str;
}

/* Returns a pointer to the first non whitespace character in a string */
char* advance_nonwhitespace (char* str) {
	if (str == NULL) return NULL;
	while (!isspace(*str) && *str != '\0') str++;
	return str;
}

/* Replaces the first whitespace character in the
 * last whitespace block of a string with \0 */
char* block_whitespace (char* str) {
	char* end;

	if (str == NULL)
		return NULL;
	if (*str == '\0')
		return str;

	end = str + strlen(str) - 1;
	while (isspace(*end) && end != str)
		end--;
	if (end != str && end != str + strlen(str)) {
		*(end + 1) = '\0';
	}
	return str;
}

/* Duplicates a string */
char* str_dup (char* str) {
	char* str_cpy;

	if (!str)
		return NULL;

	str_cpy = malloc(strlen(str) + 1);
	if (!str_cpy) {
		fprintf(stderr, ERROR_OUT_OF_MEMORY);
		exit(1);
	}

	strcpy(str_cpy, str);

	return str_cpy;
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

/* Remove comment, and split label, directive/op and arguments/operands */
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

	/* Search for first whitespace */
	*_code_contents = advance_nonwhitespace(*_name);

	/* Block it */
	if (**_code_contents == '\0')
		return;
	**_code_contents = '\0';

	/* Skip it */
	*_code_contents = advance_whitespace(*_code_contents + 1);

}

/*
 * This function check if label is in use in this file
 * return 1 if found earlier use
 * return 0 if not found earlier use
 */
int check_if_label_exists (state_t* state, char* label) {
	list* current_data_label = state->data_labels_table;
	list* current_code_label = state->code_labels_table;

	while (current_data_label != NULL) {
		if (!strcmp(((data_label*) current_data_label->data)->name, label)) {
			fprintf(stderr, ERROR_LABEL_EXISTS, label, state->current_line_num, state->current_file_name);
			return 1;
		}
		current_data_label = current_data_label->next;
	}

	while (current_code_label != NULL) {
		if (!strcmp(((code_label*) current_code_label->data)->name, label)) {
			fprintf(stderr, ERROR_LABEL_EXISTS, label, state->current_line_num, state->current_file_name);
			return 1;
		}
		current_code_label = current_code_label->next;
	}

	return 0;
}

/* Gets a label and tells if it's valid (not a register or a reserved word) */
int is_valid_label (char* name, state_t* state) {
	int i;
	size_t name_length = strlen(name); /* copy also null */
	char* name_lowercase = malloc(name_length + 1);
	long register_test;
	char* end_ptr;

	/* Labels can't start with a number */
	if (!isalpha(name[0])) {
		fprintf(stderr, ERROR_LABEL_CANNOT_START_WITH_NUM, state->current_line_num, state->current_file_name);
		free(name_lowercase);
		return 0;
	}


	/* Labels can't be equal to op names or assembly directive names, in any case, and are alphanumeric */
	for (i = 0; i < name_length; i++) {
		if (!isalnum(name[i])) {
			fprintf(stderr, ERROR_LABEL_NAME_NOT_LETTER_OR_NUM, state->current_line_num, state->current_file_name);
			free(name_lowercase);
			return 0;
		}
		name_lowercase[i] = (char) tolower(name[i]);
	}
	name_lowercase[name_length] = '\0';

	for (i = 0; i < OPS_LENGTH; i++) {
		if (!strcmp(OPS[i].name, name_lowercase)) {
			fprintf(stderr, ERROR_LABEL_NAME_IDENTICAL_OP_NAME, state->current_line_num, state->current_file_name);
			free(name_lowercase);
			return 0;
		}

	}
	for (i = 0; i < DIRECTIVES_LENGTH; i++) {
		if (!strcmp(DIRECTIVES[i].name, name_lowercase)) {
			fprintf(stderr, ERROR_LABEL_NAME_IDENTICAL_DIR_MAME, state->current_line_num, state->current_file_name);
			free(name_lowercase);
			return 0;
		}
	}

	/* Labels can't be register names */
	if (name_lowercase[0] == 'r') {
		register_test = strtol(name_lowercase + 1, &end_ptr, 10);
		if ((end_ptr != name_lowercase + 1) && (*end_ptr == '\0') && (register_test >= MINIMUM_REG) && (register_test <= MAXIMUM_REG)) {
			fprintf(stderr, ERROR_LABEL_NAME_IDENTICAL_REG_MAME, state->current_line_num, state->current_file_name);
			free(name_lowercase);
			return 0;
		}
	}

	free(name_lowercase);
	return 1;
}

data_label* find_data_label (state_t* state, char* label) {
	list* ptr;

	ptr = state->data_labels_table;
	while (ptr) {
		if (!strcmp(((data_label*) ptr->data)->name, label))
			return ptr->data;
		ptr = ptr->next;
	}

	return NULL;
}

code_label* find_code_label (state_t* state, char* label) {
	list* ptr;

	if (!label)
		return NULL;

	ptr = state->code_labels_table;
	while (ptr) {
		if (!strcmp(((code_label*) ptr->data)->name, label))
			return ptr->data;
		ptr = ptr->next;
	}

	return NULL;
}

void add_data_label (state_t* state, char* label) {
	data_label* new_label;
	char* label_cpy;

	if (!label)
		return;

	if (find_data_label(state, label)) {
		fprintf(stderr, ERROR_LABEL_EXISTS, label, state->current_line_num, state->current_file_name);
		state->failed = 1;
		return;
	}

	new_label = malloc(sizeof(data_label));
	label_cpy = str_dup(label);
	if (!new_label) {
		fprintf(stderr, ERROR_OUT_OF_MEMORY);
		exit(1);
	}

	new_label->name = label_cpy;
	new_label->address = state->data_counter;

	list_add_element(&state->data_labels_table, new_label);
}

void add_code_label (state_t* state, char* label) {
	code_label* new_label;
	char* label_cpy;

	if (!label)
		return;

	if (find_data_label(state, label)) {
		fprintf(stderr, ERROR_LABEL_EXISTS, label, state->current_line_num, state->current_file_name);
		state->failed = 1;
		return;
	}

	new_label = malloc(sizeof(code_label));
	label_cpy = str_dup(label);
	if (!new_label) {
		fprintf(stderr, ERROR_OUT_OF_MEMORY);
		exit(1);
	}

	new_label->name = label_cpy;

	list_add_element(&state->code_labels_table, new_label);
}

int is_register_valid (long reg_num) {
	return reg_num >= MINIMUM_REG && reg_num <= MAXIMUM_REG;
}

/* Checks if a labels exists in the extern table */
int is_extern_label (state_t* state, char* label) {
	list* ptr = state->extern_table;

	while (ptr) {
		if (!strcmp((char*) ptr->data, label))
			return 1;
		ptr = ptr->next;
	}

	return 0;
}

void add_ref_in_code (list** table, char* label, unsigned address) {
	list* ptr = *table;

	if (!ptr) {
		ref_in_code* ref_ptr = calloc(1, sizeof(ref_in_code));
		ptr = calloc(1, sizeof(list));
		if (!ptr || !ref_ptr) {
			fprintf(stderr, ERROR_OUT_OF_MEMORY);
			exit(1);
		}
		ptr->data = ref_ptr;
		ref_ptr->name = str_dup(label);
		ref_ptr->code_address = address;

		*table = ptr;
	} else {
		ref_in_code* ref_ptr = calloc(1, sizeof(ref_in_code));
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = calloc(1, sizeof(list));
		if (!ptr->next || !ref_ptr) {
			fprintf(stderr, ERROR_OUT_OF_MEMORY);
			exit(1);
		}
		ptr->next->data = ref_ptr;
		ref_ptr->name = str_dup(label);
		ref_ptr->code_address = address;
	}
}