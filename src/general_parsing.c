#include "general_parsing.h"
#include "errors.h"
#include "op_parser.h"
#include "directive_functions.h"
#include <string.h>
#include <ctype.h>


char* split_label_and_code (char* line) {
	int i;
	int is_in_string = 0;

	for (i = 0; i < MAX_STRING_LENGTH && line[i] != '\0'; i++) {
		if (line[i] == '"') {
			is_in_string = !is_in_string;
		} else if (line[i] == ':' && !is_in_string) {
			line[i] = '\0';
			return line + i + 1;
		}
	}

	return NULL;
}

void remove_comment (char* line) {
	int i;
	int is_in_string = 0;

	for (i = 0; i < MAX_STRING_LENGTH && line[i] != '\0'; i++) {
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

void clean_and_preprocess_line (char* line, char** _label_name, char** _code_contents, int line_num) {
	char* start_of_line;

	/* Replace `;` with `\0` so the comment is ignored */
	remove_comment(line);

	/* Trim whitespace from end */
	start_of_line = block_whitespace(line);

	/* Search for a colon, if found then split line into label
	 * ("label_name") and code ("code_contents") and skip whitespace */
	*_code_contents = advance_whitespace(split_label_and_code(start_of_line));

	if (*_code_contents == NULL) { /* No colon found */
		*_code_contents = advance_whitespace(start_of_line);
		*_label_name = NULL;
	} else if (strlen(advance_whitespace(start_of_line)) == 0) {  /* Label is empty */
		*_label_name = NULL;
		fprintf(stderr, ERROR_EMPTY_LABEL, line_num);
	} else { /* Label isn't empty */
		*_label_name = start_of_line;
		if (isspace(**_label_name)) {
			fprintf(stderr, ERROR_LABEL_NOT_ON_START_OF_LINE, line_num);
		}
		if (isspace(*(*_label_name + strlen(*_label_name) - 1))) {
			fprintf(stderr, ERROR_WHITESPACE_AFTER_LABEL, line_num);
		}
		*_label_name = block_whitespace(advance_whitespace(*_label_name));
	}
}

int is_valid_label(char *name, op_t *ops) {
	int i;
	if (isdigit(name[0]))
		return 0;

	for (i = 0; i < OP_LIST_LENGTH; i++) {
		if (!strcmp(ops[i].name, name))
			return 0;
	}

	if (name[0] == 'r') {
		if ((name[1] >= FIRST_REG) && (name[1] <= LAST_REG)) {
			return 0;
		}
	}

	char *dir_list[] = ASSEMBLER_DIRECTIVE_LIST;

	for (i = 0; i < ASSEMBLER_DIRECTIVE_LIST_LENGTH; i++)
		if (strcmp(dir_list[i], name) == 0)
			return 0;

	return 1;
}
