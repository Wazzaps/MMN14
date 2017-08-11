#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse_ops.h"
#include "constant_data.h"
#include "util_funcs.h"
#include "parse_directives.h"
#include "errors.h"
#include "parsing.h"
#include "base4.h"

int find_op (char*);

int identify_operand (char* str);

void parse_operand (int opcode, char* str, int src_type, state_t*, int combine);

void parse_ops (state_t* state) {
	char* line = malloc(LINE_LENGTH + 1);

	char* label_name = NULL;
	char* op_name = NULL;
	char* code_contents = NULL;

	state->current_line_num = 0;

	// Loop over every line
	while (get_line(line, LINE_LENGTH, state->current_file_ptr, state->current_line_num)) {
		state->current_line_num++;

		// Remove comment, and split label, directive/op and arguments/operands
		clean_and_split_line(line, &label_name, &op_name, &code_contents, state, 0);

		// Check op name and label
		if (op_name && !ISDIRECTIVE(op_name) &&
			(!label_name || is_valid_label(label_name, state->current_line_num, state->current_file_name))) {
			int opcode = find_op(op_name);

			if (opcode != -1) {
				op_t my_op = OPS[opcode];

				cpu_word* op_word = add_word(&state->code_table, &state->code_counter, 0);

				int number_of_operands = my_op.number_of_operands;

				// Split operands by '\0' instead of comma
				char* second_operand_string = strchr(code_contents, ',');
				if (second_operand_string) {
					*second_operand_string = '\0';
					second_operand_string++;
				}

				// Push the label to the table, with it's final address
				if (label_name) {
					// TODO - check me
					code_label *new_label = malloc(sizeof(code_label));
					new_label->name = label_name;
					new_label->code_address = state->code_counter;

					list_add_element(&state->code_labels_table, new_label);
				}

				if (number_of_operands >= 1) {
					int src_type = identify_operand(code_contents);
					if (src_type == -1) {
						fprintf(stderr, ERROR_MISSING_FIRST_OPERAND, state->current_line_num,
						        state->current_file_name);
						state->failed = 1;
						continue;
					}

					parse_operand(opcode, code_contents, src_type, state, 0);

					if (number_of_operands == 2) {
						int dst_type = identify_operand(second_operand_string);
						if (dst_type == -1) {
							fprintf(stderr, ERROR_MISSING_SECOND_OPERAND, state->current_line_num,
							        state->current_file_name);
							state->failed = 1;
							continue;
						}

						*op_word = (opcode << 6) | (src_type << 4) | (dst_type << 2);
						parse_operand(opcode, second_operand_string, src_type, state, src_type == REGIS && dst_type == REGIS);
					} else {
						*op_word = (opcode << 6) | (src_type << 2);
					}
				} else {
					*op_word = opcode << 6;
				}
			} else {
				fprintf(stderr, ERROR_UNKNOWN_OP, op_name, state->current_line_num, state->current_file_name);
			}
		}
	}
}

int find_op (char* directive_name) {
	int i;

	for (i = 0; i < OPS_LENGTH; i++)
		if (!strcmp(directive_name, OPS[i].name))
			return i;

	return -1;
}

int identify_operand (char* str) {
	char* ptr;
	long tmp_number;

	// NULL check
	if (!str) return -1;

	// Starts with a digit = fail
	if (isdigit(str[0])) return -1;

	// 'r' + number = register
	ptr = str + 1;
	if (tolower(*str) == 'r' && MAYBE_NUMBER(tmp_number) && *ptr == '\0')
		return 3;

	ptr = str;
	// alpha + alphanumeric[] = label
	if (isalpha(*ptr)) {
		while (1) {
			if (isalnum(*ptr)) {
				ptr++;
			} else if (*ptr != '\0') {
				break;
			} else {
				return 1;
			}
		}
	}

	ptr = str + 1;
	// '#' + number = immediate
	if (*str == '#' && MAYBE_NUMBER(tmp_number) && *ptr == '\0')
		return 0;

	ptr = str;
	// alpha + alphanumeric[] + '[' + number + ']' + '[' + number + ']' = matrix
	if (isalpha(*ptr)) {
		while (1) {
			if (isalnum(*ptr)) {
				ptr++;
			} else if (*(ptr++) == '[' && tolower(*(ptr++)) == 'r' && MAYBE_NUMBER(tmp_number) && *(ptr++) == ']' &&
			           *(ptr++) == '[' && tolower(*(ptr++)) == 'r' && MAYBE_NUMBER(tmp_number) && *(ptr++) == ']' &&
			           *ptr == '\0') {
				return 2;
			} else {
				break;
			}
		}
	}


	// Default = fail
	return -1;
}

void parse_operand (int opcode, char* str, int src_type, state_t* state, int combine) {
    char* endptr = str + 1;
    int number;

    if (str[0] == '#') {  // Direct addressing
        number = strtol(endptr, &endptr, 10);
        if (endptr == NULL) {
            fprintf(stderr, ERROR_INVALID_OPERATOR, state->current_line_num, state->current_file_name);
            return;
        }
        number = number << 2;

        add_word(&state->code_table, &state->code_counter, number);
        if ((strtok(str, ",") == NULL) &&
            advance_whitespace(endptr) != '\0') { // if its the sec operand and its not end of line
            fprintf(stderr, ERROR_UNNECESSSARY_OPERATOR, state->current_line_num, state->current_file_name);
            return;
        }
    }

    //When dealing with labels, you need to check if they are external, then set ERA flags


	/*
	// Need this for when combine == 1
	// Src = SSSS.0000.EE
	// Dst = DDDD.0000.EE
	// Out = Src | Dst>>4
	// Out = SSSS.DDDD.EE

	src_operand = src_operand | dst_operand >> 4;
	*/

	/*
	// Finish with this
    if (*str != '\0') {
		fprintf(stderr, ERROR_UNEXPECTED_TEXT, code_contents, state->current_line_num,
		        state->current_file_name);
		state->failed = 1;
	}
	*/
}
