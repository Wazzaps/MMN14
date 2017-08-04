#include <string.h>
#include "op_parser.h"
#include "general_parsing.h"
#include "util_functions.h"
#include "errors.h"

int parse_ops (FILE* fp, string file_name, struct assembler_state_tables* tables) {
	int success = 1;
	string line = "";
	unsigned int line_num = 1;
	int line_length = 0;

	/* Define tables for parser and jump table */
	parser_definition custom_types[] = PARSER_CUSTOM_TYPES;
	op_t ops[OP_LIST_LENGTH] = {
			{"mov",  2, "%{reg|const|mataccess|label},%{reg|disabled|mataccess|label}"},
			{"cmp",  2, "%{reg|const|mataccess|label},%{reg|const|mataccess|label}"},
			{"add",  2, "%{reg|const|mataccess|label},%{reg|disabled|mataccess|label}"},
			{"sub",  2, "%{reg|const|mataccess|label},%{reg|disabled|mataccess|label}"},
			{"not",  1, "%{reg|disabled|mataccess|label}"},
			{"clr",  1, "%{reg|disabled|mataccess|label}"},
			{"lea",  2, "%{disabled|disabled|mataccess|label},%{reg|disabled|mataccess|label}"},
			{"inc",  1, "%{reg|disabled|mataccess|label}"},
			{"dec",  1, "%{reg|disabled|mataccess|label}"},
			{"jmp",  1, "%{reg|disabled|mataccess|label}"},
			{"bne",  1, "%{reg|disabled|mataccess|label}"},
			{"red",  1, "%{reg|disabled|mataccess|label}"},
			{"prn",  1, "%{reg|const|mataccess|label}"},
			{"jsr",  1, "%{reg|disabled|mataccess|label}"},
			{"rts",  0, ""},
			{"stop", 0, ""}
	};

	/* Read each line */
	while ((line_length = get_line(line, MAX_STRING_LENGTH + 1, fp)) != -1) {
		char* code_contents = NULL;
		char* label_name = NULL;
		char* op_name = NULL;
		void* parse_struct;
		int i;
		int op_exists = 0;

		/* Check that line length isn't over the limit */
		if (line_length == MAX_STRING_LENGTH) {
			fprintf(stderr, ERROR_LINE_TOO_LONG, line_num, file_name, MAX_STRING_LENGTH);
		}

		clean_and_preprocess_line(line, &label_name, &code_contents, line_num);

		if (label_name != NULL) {
			if (strlen(label_name) > MAX_LABEL_NAME_LENGTH) {
				fprintf(stderr, ERROR_LABEL_TOO_LONG, MAX_LABEL_NAME_LENGTH, line_num);
			}

			if (code_contents[0] == '\0') {
				fprintf(stderr, ERROR_USELESS_LABEL, line_num);
			}

			if (is_valid_label(label_name, ops) == 0) {
				fprintf(stderr, ERROR_LABEL_NAME, line_num);
			}
		}

		if (code_contents[0] == '.' || code_contents[0] == '\0') {
			line_num++;
			continue;
		}

		// Split op name and parameters
		op_name = code_contents;

		while (*code_contents != ' ' && *code_contents != '\t' && *code_contents != '\0') code_contents++;
		if (*code_contents != '\0') { // If no arguments after op name, make sure to not corrupt memory
			*code_contents = '\0';
			code_contents = advance_whitespace(code_contents + 1);
		}

		// Check that the op name is valid
		for (i = 0; i < OP_LIST_LENGTH; i++) {
			if (!strcmp(ops[i].name, op_name)) {
				op_exists = 1;

				parse_struct = mysscanf(ops[i].format, PARSER_CUSTOM_TYPES_LENGTH, custom_types, code_contents, 1,
				                        line_num);

				if (parse_struct) {

					//* element_code(op_name, ); *//
					// TODO: Convert and lay out parsed info to final binary structure
					// TODO: NOTE: OPs with 1 arg put their data in target operand, not source

					// TODO: Put parsed op in code table
				} else {
					printf("Failed: %s %s\n", ops[i].format, code_contents);
					success = 0;
				}

				break;
			}
		}

		if (!op_exists) {
			// OP not found, complain
			fprintf(stderr, ERROR_UNKNOWN_OP, op_name, line_num);
			success = 0;
		}

		line_num++;

	}
	// sldkfjlk

	/* sdfsdf
	 * */

// list *iterator = tables->data_labels_table;

//*    memcpy(tables->data, tables->code + tables->code_current_size, tables->data_current_size);
//*    while ( iterator->next != NULL){
//*        ((data_label *)iterator->data)->data_address += tables->code_current_size;
//*        iterator = iterator->next;
//*    }

	return success;
}