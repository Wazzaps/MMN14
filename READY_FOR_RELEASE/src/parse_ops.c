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

void parse_operand (char* str, int type, state_t*, int combine, operand_type_e operand_type);

void parse_ops (state_t* state) {
	char* line = malloc(LINE_LENGTH + 1);

	char* label_name = NULL;
	char* op_name = NULL;
	char* code_contents = NULL;

	state->current_line_num = 0;

	/* Loop over every line */
	while (get_line(line, LINE_LENGTH, state->current_file_ptr, state->current_line_num)) {
		state->current_line_num++;

		/* Remove comment, and split label, directive/op and arguments/operands */
		clean_and_split_line(line, &label_name, &op_name, &code_contents, state, 0);

		/* Check op name and label */
		if (op_name && !ISDIRECTIVE(op_name) &&
		    (!label_name || is_valid_label(label_name, state))) {
			int opcode = find_op(op_name);

			/* Put the address in the label allocated by find_directives_and_labels() */
			if (label_name)
				find_code_label(state, label_name)->address = state->code_counter;

			if (opcode != -1) {
				op_t my_op = OPS[opcode];

				unsigned op_word_index = add_word(&state->code_table, &state->code_counter, 0);

				int number_of_operands = my_op.number_of_operands;

				/* Split operands by '\0' instead of comma */
				char* second_operand_string = strchr(code_contents, ',');
				if (second_operand_string) {
					*second_operand_string = '\0';
					second_operand_string++;
				}

				second_operand_string = advance_whitespace(second_operand_string);

				/* Push the label to the table, with it's final address */
				if (label_name) {
					add_code_label(state, label_name);
				}

				if (number_of_operands >= 1) {
					int src_type = identify_operand(code_contents);
					if (src_type == -1) {
						fprintf(stderr, ERROR_MISSING_FIRST_OPERAND, state->current_line_num, state->current_file_name);
						state->failed = 1;
						continue;
					} else if (!(my_op.src_t & (1 << src_type))) {
						fprintf(stderr, ERROR_UNSUPPORTED_OPERAND_TYPE, op_name, code_contents, state->current_line_num, state->current_file_name);
						state->failed = 1;
						continue;
					}

					parse_operand(code_contents, src_type, state, 0, number_of_operands == 2 ? SRC : DST);

					if (number_of_operands == 2) {
						int dst_type = identify_operand(second_operand_string);
						if (dst_type == -1) {
							fprintf(stderr, ERROR_MISSING_SECOND_OPERAND, state->current_line_num, state->current_file_name);
							state->failed = 1;
							continue;
						} else if (!(my_op.dst_t & (1 << dst_type))) {
							fprintf(stderr, ERROR_UNSUPPORTED_OPERAND_TYPE, op_name, second_operand_string, state->current_line_num, state->current_file_name);
							state->failed = 1;
							continue;
						}

						*(state->code_table + op_word_index) = (opcode << 6) | (src_type << 4) | (dst_type << 2);
						parse_operand(second_operand_string, dst_type, state, src_type == 3 && dst_type == 3, DST);
					} else {
						*(state->code_table + op_word_index) = (opcode << 6) | (src_type << 2);
						if (second_operand_string && *second_operand_string != '\0') {
							fprintf(stderr, ERROR_EXPECTED_EOL, second_operand_string, state->current_line_num, state->current_file_name);
							state->failed = 1;
							continue;
						}
					}
				} else {
					*(state->code_table + op_word_index) = opcode << 6;
					if (code_contents && *code_contents != '\0') {
						fprintf(stderr, ERROR_EXPECTED_EOL, code_contents, state->current_line_num, state->current_file_name);
						state->failed = 1;
						continue;
					}
				}

			} else {
				fprintf(stderr, ERROR_UNKNOWN_OP, op_name, state->current_line_num, state->current_file_name);
			}
		}
	}
	free(line);
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

	/* NULL check */
	if (!str)
		return -1;

	/* Starts with a digit = fail */
	if (isdigit(str[0]))
		return -1;

	/* 'r' + number = register */
	ptr = str + 1;
	if (tolower(*str) == 'r' && MAYBE_NUMBER(tmp_number) && is_register_valid(tmp_number) && *ptr == '\0')
		return 3; /* 3 = REGISTER */

	ptr = str;
	/* alpha + alphanumeric[] = label */
	if (isalpha(*ptr)) {
		while (1) {
			if (isalnum(*ptr)) {
				ptr++;
			} else if (*ptr != '\0') {
				break;
			} else {
				return 1; /* 1 = LABEL */
			}
		}
	}

	ptr = str + 1;
	/* '#' + number = immediate */
	if (*str == '#' && MAYBE_NUMBER(tmp_number) && *ptr == '\0')
		return 0; /* 0 = IMMEDIATE */

	ptr = str;
	/* alpha + alphanumeric[] + '[' + number + ']' + '[' + number + ']' = matrix */
	if (isalpha(*ptr)) {
		while (1) {
			if (isalnum(*ptr)) {
				ptr++;
			} else if (*(ptr++) == '[' && tolower(*(ptr++)) == 'r' && MAYBE_NUMBER(tmp_number) && *(ptr++) == ']' &&
			           *(ptr++) == '[' && tolower(*(ptr++)) == 'r' && MAYBE_NUMBER(tmp_number) && *(ptr++) == ']' &&
			           *ptr == '\0') {
				return 2; /* 2 = MATRIX */
			} else {
				break;
			}
		}
	}


	/* Default = fail */
	return -1;
}


void parse_operand (char* str, int type, state_t* state, int combine, operand_type_e operand_type) {
	/* Practically no error checking is done because it was done in identify_operand */
	if (type == 0) { /* 0 = IMMEDIATE */

		char* ptr = str + 1;
		long num;

		EXPECT_NUMBER(num);

		if (num < MIN_VALUE_SIGNED_8bits || num > MAX_VALUE_SIGNED_8bits) {
			fprintf(stderr, ERROR_DATA_OUT_OF_BOUNDS, num, MIN_VALUE_SIGNED_8bits, MAX_VALUE_SIGNED_8bits,
			        state->current_line_num, state->current_file_name);
			state->failed = 1;
			return;
		}

		add_word(&state->code_table, &state->code_counter, (cpu_word) num << 2 | ABSOLUTE);

	} else if (type == 1) { /* 1 = LABEL */

		if (!is_valid_label(str, state)) {
			return;
		}

		if (is_extern_label(state, str)) {
			/* Adds the extern word to the code table, and saves it's index, in the extern refs table */
			add_ref_in_code(&state->extern_refs_table, str, add_word(&state->code_table, &state->code_counter, EXTERNAL));
		} else if (find_data_label(state, str)) {
			int label_address = find_data_label(state, str)->address;
			add_word(&state->code_table, &state->code_counter, label_address << 2 | RELOCATABLE);
		} else if (find_code_label(state, str)) {
			/* Adds a "code label" marker to the code table, and saves it's index in the code label refs table for later replacement */
			unsigned index = add_word(&state->code_table, &state->code_counter, CODE_LABEL);
			add_ref_in_code(&state->code_label_refs_table, str, index);
		} else {
			fprintf(stderr, ERROR_LABEL_DOESNT_EXIST, str, state->current_line_num, state->current_file_name);
			state->failed = 1;
			return;
		}

	} else if (type == 2) { /* 2 = MATRIX */

		char* ptr;
		int label_address;
		long mat_x;
		long mat_y;


		/* Split "LABEL[r1][r2]"           */
		/*             ^ Here              */
		/* By replacing the '[' with '\0'  */
		ptr = strchr(str, '[');
		*ptr = '\0';

		/* Jump to the first register number */
		ptr += 2; /* skip "[r" */

		EXPECT_NUMBER(mat_x);

		if (!is_register_valid(mat_x)) {
			fprintf(stderr, ERROR_REGISTER_OUT_OF_BOUNDS, mat_x, state->current_line_num, MINIMUM_REG, MAXIMUM_REG, state->current_file_name);
			state->failed = 1;
			return;
		}

		/* Jump to the second register number */
		ptr += 3; /* skip "][r" */

		EXPECT_NUMBER(mat_y);

		if (!is_register_valid(mat_y)) {
			fprintf(stderr, ERROR_REGISTER_OUT_OF_BOUNDS, mat_y, MINIMUM_REG, MAXIMUM_REG, state->current_line_num, state->current_file_name);
			state->failed = 1;
			return;
		}

		if (!is_register_valid(mat_x) || !is_register_valid(mat_y))
			return;

		if (is_extern_label(state, str)) {
			add_ref_in_code(&state->extern_refs_table, str, add_word(&state->code_table, &state->code_counter, EXTERNAL));
		} else if (find_code_label(state, str)) {
			fprintf(stderr, ERROR_CODE_LABEL_IN_MATRIX, str, state->current_line_num, state->current_file_name);
			state->failed = 1;
			return;
		} else {
			data_label* current;
			if ((current = find_data_label(state, str))) {
				label_address = current->address;
				add_word(&state->code_table, &state->code_counter, label_address << 2 | RELOCATABLE);
			} else {
				fprintf(stderr, ERROR_LABEL_DOESNT_EXIST, str, state->current_line_num, state->current_file_name);
				state->failed = 1;
				return;
			}
		}

		add_word(&state->code_table, &state->code_counter, (cpu_word) (mat_x << 6 | mat_y << 2) | ABSOLUTE);

	} else if (type == 3) { /* 3 = REGISTER */

		char* ptr = str + 1; /* skip 'r' */
		long reg_num;

		EXPECT_NUMBER(reg_num);

		if (!is_register_valid(reg_num)) {
			fprintf(stderr, ERROR_REGISTER_OUT_OF_BOUNDS, reg_num, MINIMUM_REG, MAXIMUM_REG, state->current_line_num, state->current_file_name);
			state->failed = 1;
			return;
		}

		if (!combine) {
			add_word(&state->code_table, &state->code_counter, (cpu_word) (reg_num << (operand_type == SRC ? 6 : 2)) | ABSOLUTE);
		} else {
			cpu_word word = state->code_table[state->code_counter - 1] - ABSOLUTE; /* Remove abs flag */
			word |= (cpu_word) reg_num << 2 | ABSOLUTE; /* Add dst register and abs flag back */
			state->code_table[state->code_counter - 1] = word;
		}

	}
}