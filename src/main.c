
#include "directive_parser.h"
#include <string.h>
#include <stdlib.h>
#include "errors.h"
#include "op_parser.h"

int main (int argc, char* argv[]) {
	int iterator;
	int failed_file_check = 0;

	/* Check that file arguments are valid */
	if (argc == 1) {
		fprintf(stderr, ERROR_NO_INPUT_FILES);
		return 1;
	}

	/* Open files */
	for (iterator = 1; iterator < argc; iterator++) {
		/* Add .as extension */
		string file_name = {};
		strcpy(file_name, argv[iterator]);
		strcat(file_name, ".as");

		/* Check that all files can be read */
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
		int success = 1;

		/* Create relevant tables */
		struct assembler_state_tables tables;
		tables.data = malloc(1);
		tables.code = malloc(1);
		tables.extern_table = NULL;
		tables.entry_table = NULL;
		tables.code_labels_table = NULL;
		tables.data_labels_table = NULL;
		tables.code_current_size = 0;
		tables.data_current_size = 0;

		/* Create file name */
		string file_name = {};
		strcpy(file_name, argv[iterator]);
		strcat(file_name, ".as");
		FILE* file = fopen(file_name, "r");
		if (DEBUG_MODE) {
			printf("Processing file: %s\n", file_name);
		}

		/* Parse */
		success = parse_directives_and_labels(file, argv[iterator], &tables)
		          && success;
		success = parse_ops(file, argv[iterator], &tables)
		          && success;

		if (success) {
			//list* ptr = tables.extern_table;


		}

		/* Close file */
		fclose(file);

		if (DEBUG_MODE) {
			printf("%s\n", success ? "Success!" : "Fail!");
		}
	}

	return 0;
}