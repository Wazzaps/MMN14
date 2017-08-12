#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse_ops.h"
#include "constant_data.h"
#include "util_funcs.h"
#include "parse_directives.h"
#include "errors.h"
#include "parsing.h"
#include "state.h"

int find_op (char*);

int identify_operand (char* str);

void parse_operand (int opcode, char* str, int type, state_t*, int combine, operand_type_e operand_type);

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

			if (label_name)
				find_code_label(state, label_name)->address = state->data_counter + state->code_counter;

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

				second_operand_string = advance_whitespace(second_operand_string);

				// Push the label to the table, with it's final address
				if (label_name) {
					add_code_label(state, label_name);
				}


				if (number_of_operands >= 1) {
					int src_type = identify_operand(code_contents);
					if (src_type == -1) {
						fprintf(stderr, ERROR_MISSING_FIRST_OPERAND, state->current_line_num,
						        state->current_file_name);
						state->failed = 1;
						continue;
					}

					parse_operand(opcode, code_contents, src_type, state, 0, 0);

					if (number_of_operands == 2) {
						int dst_type = identify_operand(second_operand_string);
						if (dst_type == -1) {
							fprintf(stderr, ERROR_MISSING_SECOND_OPERAND, state->current_line_num,
							        state->current_file_name);
							state->failed = 1;
							continue;
						}

						*op_word = (opcode << 6) | (src_type << 4) | (dst_type << 2);
						parse_operand(opcode, second_operand_string, dst_type, state, src_type == 3 && dst_type == 3, 1);
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
	if (!str)
		return -1;

	// Starts with a digit = fail
	if (isdigit(str[0]))
		return -1;

	// 'r' + number = register
	ptr = str + 1;
	if (tolower(*str) == 'r' && MAYBE_NUMBER(tmp_number) && *ptr == '\0')
		return 3; // 3 = REGISTER

	ptr = str;
	// alpha + alphanumeric[] = label
	if (isalpha(*ptr)) {
		while (1) {
			if (isalnum(*ptr)) {
				ptr++;
			} else if (*ptr != '\0') {
				break;
			} else {
				return 1; // 1 = LABEL
			}
		}
	}

	ptr = str + 1;
	// '#' + number = immediate
	if (*str == '#' && MAYBE_NUMBER(tmp_number) && *ptr == '\0')
		return 0; // 0 = IMMEDIATE

	ptr = str;
	// alpha + alphanumeric[] + '[' + number + ']' + '[' + number + ']' = matrix
	if (isalpha(*ptr)) {
		while (1) {
			if (isalnum(*ptr)) {
				ptr++;
			} else if (*(ptr++) == '[' && tolower(*(ptr++)) == 'r' && MAYBE_NUMBER(tmp_number) && *(ptr++) == ']' &&
			           *(ptr++) == '[' && tolower(*(ptr++)) == 'r' && MAYBE_NUMBER(tmp_number) && *(ptr++) == ']' &&
			           *ptr == '\0') {
				return 2; // 2 = MATRIX
			} else {
				break;
			}
		}
	}


	// Default = fail
	return -1;
}


void parse_operand (int opcode, char* str, int type, state_t* state, int combine, operand_type_e operand_type) {
	// Practically no error checking is done because it was done in identify_operand
	if (type == 0) { // 0 = IMMEDIATE

		char* ptr = str + 1;
		long num;

		EXPECT_NUMBER(num);

		add_word(&state->code_table, &state->code_counter, (cpu_word) num << 2 | ABSOLUTE);

	} else if (type == 1) { // 1 = LABEL

		if (!is_valid_label(str, state->current_line_num, state->current_file_name)) {
			return;
		}

		if (is_extern_label(state, str)) {
			// Adds the extern word to the code table, and saves it's index in the extern refs table
			add_ref_in_code(&state->extern_refs_table, str, (unsigned) (add_word(&state->code_table, &state->code_counter, EXTERNAL) - state->code_table));
		} else if (find_data_label(state, str)) {
			int label_address = get_data_label_address(state, str);
			add_word(&state->code_table, &state->code_counter, label_address << 2 | RELOCATABLE);
		} else if (find_code_label(state, str)) {
			// Adds a "code label" marker to the code table, and saves it's index in the code label refs table for later replacement
			cpu_word* new_word = add_word(&state->code_table, &state->code_counter, CODE_LABEL);
			unsigned index = (unsigned)(new_word - state->code_table);
			add_ref_in_code(&state->code_label_refs_table, str, index);
		} else {
			fprintf(stderr, ERROR_LABEL_DOESNT_EXIST, str, state->current_line_num, state->current_file_name);
			state->failed = 1;
		}

	} else if (type == 2) { // 2 = MATRIX

		char* ptr;
		int label_address;
		long mat_x;
		long mat_y;


		// Split "LABEL[r1][r2]"
		//             ^ Here
		// By replacing the '[' with '\0'
		ptr = strchr(str, '[');
		*ptr = '\0';

		// Jump to the first register number
		ptr += 2; // skip "[r"

		EXPECT_NUMBER(mat_x);

		if (!is_register_valid(mat_x)) {
			fprintf(stderr, ERROR_REGISTER_OUT_OF_BOUNDS, mat_x, state->current_line_num, state->current_file_name);
			state->failed = 1;
		}

		// Jump to the second register number
		ptr += 3; // skip "][r"

		EXPECT_NUMBER(mat_y);

		if (!is_register_valid(mat_y)) {
			fprintf(stderr, ERROR_REGISTER_OUT_OF_BOUNDS, mat_y, state->current_line_num, state->current_file_name);
			state->failed = 1;
		}

		if (!is_register_valid(mat_x) || !is_register_valid(mat_y))
			return;

		if (is_extern_label(state, str)) {
			add_ref_in_code(&state->extern_refs_table, str,
			                (unsigned) (state->code_table - add_word(&state->code_table, &state->code_counter, EXTERNAL))
			);
		} else if (find_code_label(state, str)) {
			fprintf(stderr, ERROR_CODE_LABEL_IN_MATRIX, str, state->current_line_num, state->current_file_name);
			state->failed = 1;
		} else {
			label_address = get_data_label_address(state, str);
			add_word(&state->code_table, &state->code_counter, label_address << 2 | RELOCATABLE);
		}

		add_word(&state->code_table, &state->code_counter, (cpu_word)(mat_x << 6 | mat_y << 2) | ABSOLUTE);

	} else if (type == 3) { // 3 = REGISTER

		char* ptr = str + 1; // skip 'r'
		long reg_num;

		EXPECT_NUMBER(reg_num);

		if (!is_register_valid(reg_num)) {
			fprintf(stderr, ERROR_REGISTER_OUT_OF_BOUNDS, reg_num, state->current_line_num, state->current_file_name);
			state->failed = 1;
		}

		if (!combine) {
			add_word(&state->code_table, &state->code_counter, (cpu_word)(reg_num << (operand_type == SRC ? 6 : 2)) | ABSOLUTE);
		} else {
			cpu_word word = state->code_table[state->code_counter - 1] - ABSOLUTE; // Remove abs flag
			word |= (cpu_word)reg_num << 2 | ABSOLUTE; // Add dst register and abs flag back
			state->code_table[state->code_counter - 1] = word;
		}

	}
	/*
    char* endptr = str + 1;
    double number;

    if (str[0] == '#') {
        number = strtod(endptr, &endptr);
        if ( endptr == NULL ) {
            fprintf(stderr, ERROR_INVALID_OPERATOR,  state->current_line_num, state->current_file_name);
            return ;
        }

        add_word(&state->code_table, &state->code_counter, number);
        if ( (strtok(str, ",") == NULL) && advance_whitespace(endptr) != '\0' ) { // if its the sec operand and its not end of line
            fprintf(stderr, ERROR_UNNECESSSARY_OPERATOR,  state->current_line_num, state->current_file_name);
            return ;
        }
    }//*/
	/*
	 When dealing with labels, you need to check if they are external, then set ERA flags
	 */

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