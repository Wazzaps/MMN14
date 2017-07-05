#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "errors.h"
#include "directive_parser.h"

int main (int argc, char* argv[]) {
	int iterator;
	int failed_file_check = 0;
	void* ptr;
	int len;
	int i;

	/* Check that file arguments are valid */
	if (argc == 1) {
		fprintf(stderr, ERROR_NO_INPUT_FILES);
		return 1;
	}

	for (iterator = 1; iterator < argc; iterator++) {
		string file_name = {};
		strcpy(file_name, argv[iterator]);
		strcat(file_name, ".as");
		FILE* file = fopen(file_name, "r");
		if (file == NULL) {
			fprintf(stderr, ERROR_CANNOT_READ, argv[iterator]);
			failed_file_check = 1;
		}
		fclose(file);
	}

	if (failed_file_check)
		return 1;

	/* Open files */
	for (iterator = 1; iterator < argc; iterator++) {
		string file_name = {};
		strcpy(file_name, argv[iterator]);
		strcat(file_name, ".as");
		FILE* file = fopen(file_name, "r");
		if (DEBUG_MODE) {
			printf("Opening file: %s\n", file_name);
		}

		/* Create relevant tables */
		entry_list* entry_table;
		extern_list* extern_table;
		label_list* label_table;

		parse_directives(file, argv[iterator], *&entry_table, *&extern_table, *&label_table);

		/* Close file */
		fclose(file);
	}

	/*ptr = mysscanf("%{string}", 26, custom_types, "\"Hello\"", 1);
	if (!ptr) {
		printf("Parser failed gracefully!\n");
	} else {
		len = PARSER_GET_INT(ptr); // Mat init length
		for (i = 0; i < len; i++) {
			printf("%c", PARSER_GET_CHAR(ptr)); // Mat init value(s)
		}
	}*/

	return 0;
}