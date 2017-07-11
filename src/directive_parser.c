//
// Created by david on 6/17/17.
//

#include <string.h>
#include <ctype.h>
#include "structures.h"
#include "util_functions.h"
#include "errors.h"
#include "string_parser.h"
#include "general_parsing.h"
#include "individual_directives_and_ops.h"

/* Reads assembly directives */
void parse_directives (FILE* fp, string file_name, list** entry_list, list** extern_list,
                       list** label_list, dataptr* data, codeptr* code) {
	string line = "";
	unsigned int line_num = 1;
	int line_length = 0;

	parser_definition custom_types[] = PARSER_CUSTOM_TYPES;
	op assembler_directives[ASSEMBLER_DIRECTIVE_LIST_LENGTH] = {
			OP(data),
			OP(string),
			OP(mat),
			OP(entry),
			OP(extern)
	};

	/* Read each line for pass 1 (assembly directives) */
	while ((line_length = get_line(line, MAX_STRING_LENGTH + 1, fp)) != -1) {
		char* code_contents;
		char* label_name;
		char* directive_name;
		string fmt = "%{";
		void* parse_struct;
		int i;
		int directive_exists = 0;

		/* Check that line length isn't over the limit */
		if (line_length == MAX_STRING_LENGTH) {
			fprintf(stderr, ERROR_LINE_TOO_LONG, line_num, file_name, MAX_STRING_LENGTH);
		}

		clean_and_preprocess_line(line, &label_name, &code_contents, line_num);

		if (label_name != NULL && strlen(label_name) > MAX_LABEL_NAME_LENGTH) {
			fprintf(stderr, ERROR_LABEL_TOO_LONG, MAX_LABEL_NAME_LENGTH, line_num);
		}

		if (label_name != NULL && code_contents[0] == '\0') {
			fprintf(stderr, ERROR_USELESS_LABEL, line_num);
		}


		if (code_contents[0] != '.')
			continue;

		// Test for no space between dot and directive name
		if (isblank(code_contents[1])) {
			fprintf(stderr, ERROR_WHITESPACE_BEFORE_DIRECTIVE, line_num);
			code_contents = advance_whitespace(code_contents + 1);
		} else {
			code_contents++;
		}

		// Split op/directive name and parameters
		{
			directive_name = code_contents;

			while (*code_contents != ' ' && *code_contents != '\t' && *code_contents != '\0') code_contents++;
			*code_contents = '\0';
			code_contents = advance_whitespace(code_contents + 1);
		}

		// Check that the directive is valid
		for (i = 0; i < ASSEMBLER_DIRECTIVE_LIST_LENGTH; i++) {
			if (!strcmp(assembler_directives[i].name, directive_name)) {
				directive_exists = 1;

				// Construct format string
				strcat(fmt, directive_name);
				strcat(fmt, "}");

				parse_struct = mysscanf(fmt, PARSER_CUSTOM_TYPES_LENGTH, custom_types, code_contents, 1);

				if (parse_struct) {
					assembler_directives[i].func(parse_struct, entry_list, extern_list,
					                             label_list, data, code, line_num);
				}

				break;
			}
		}

		if (!directive_exists) {
			// Directive not found, complain
			fprintf(stderr, ERROR_WHITESPACE_BEFORE_DIRECTIVE, line_num);
		}

		line_num++;

	}
}