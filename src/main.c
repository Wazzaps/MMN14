#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structures.h"
#include "errors.h"
#include "directive_parser.h"

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

		if (success) {
			list* ptr = tables.extern_table;

			/*if (tables.entry_table != NULL) {
				list* ptr = label_table;
				string entry_file_name = {};

				strcpy(entry_file_name, argv[iterator]);
				strcat(entry_file_name, ".ent");
				FILE* entry_file = fopen(entry_file_name, "w");

				while (ptr != NULL) {
					int i;
					char* base4_converted = to_base4(ptr->number);

					fprintf(entry_file, "%s", ptr->name);
					for (i = (int)strlen(ptr->name); i < ENT_AND_EXT_PADDING; i++) {
						putc(' ', entry_file);
					}
					fprintf(entry_file, "%s\n", base4_converted);
					free(base4_converted);

					ptr = ptr->next;
				}

				fclose(entry_file);
			}*/


		}

		//free(data);
		//free(code);

		/* Close file */
		fclose(file);

		if (DEBUG_MODE) {
			printf("%s\n", success ? "Success!" : "Fail!");
		}
	}

	return 0;
}