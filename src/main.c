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
		/* Create relevant tables */
		list* entry_table = NULL;
		list* extern_table = NULL;
		list* label_table = NULL;
		dataptr data = malloc(1);
		codeptr code = malloc(1);

		/* Create file name */
		string file_name = {};
		strcpy(file_name, argv[iterator]);
		strcat(file_name, ".as");
		FILE* file = fopen(file_name, "r");
		if (DEBUG_MODE) {
			printf("Opening file: %s\n", file_name);
		}

		/* Parse */
		parse_directives(file, argv[iterator], &entry_table, &extern_table, &label_table, &data, &code);

		/* FIXME: Print all entries as an example */
		{
			list* ptr = entry_table;
			while (ptr != NULL) {
				printf("%s : %d\n", ptr->name, ptr->line_num);
				ptr = ptr->next;
			}
		}

		free(data);
		free(code);

		/* Close file */
		fclose(file);
	}

	return 0;
}