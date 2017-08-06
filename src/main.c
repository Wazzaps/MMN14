
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "state.h"
#include "util_funcs.h"
#include "parse_directives.h"
#include "parse_ops.h"
#include "errors.h"

#define DEBUG_MODE 1

int main (int argc, char* argv[]) {
	int iterator;
	int all_success = 1;

	/* Check that file arguments are valid */
	if (argc == 1) {
		fprintf(stderr, ERROR_NO_INPUT_FILES);
		return 1;
	}

	/* Open files */
	for (iterator = 1; iterator < argc; iterator++) {
		state_t state;
		char* file_name = file_add_extension(argv[iterator], "as");

		/* Create relevant tables - Setup state table */
		state.data_table = malloc(1);
		state.data_counter = 0;
		state.code_table = malloc(1);
		state.code_counter = 0;
		state.extern_table = NULL;
		state.entry_table = NULL;
		state.code_labels_table = NULL;
		state.data_labels_table = NULL;

		state.current_file_name = argv[iterator];
		state.current_line_num = 0;
		state.failed = 0;

		/* Make sure the file exists */
		FILE* fp = fopen(file_name, "r");
		if (fp) {
			printf("Processing file: %s\n", file_name);
			state.current_file_ptr = fp;
		} else {
			fprintf(stderr, ERROR_CANNOT_READ, argv[iterator]);
			continue;
		}

		/* Parse */
		parse_directives_and_labels(&state);
		parse_ops(&state);

		/* Close file */
		fclose(fp);

		/* Write data to file */
		if (!state.failed) {
			//list* ptr = tables.extern_table;
			char* output_ob_file_name = file_add_extension(argv[iterator], "ob");
			FILE *output_ob_file = fopen(output_ob_file_name, "w");

			// TODO: Add code size to all addresses in code
			// TODO: Write the file, with a 100 offset in address


			fclose(output_ob_file);
			free(output_ob_file_name);

			if (state.entry_table != NULL) {
				char* output_ent_file_name = file_add_extension(argv[iterator], "ent");
				FILE *output_ent_file = fopen(output_ent_file_name, "w");

				// Go over all entry table
				// For each entry get it's label's address
				// Write that in the file

				fclose(output_ent_file);
				free(output_ent_file_name);
			}

			if (state.extern_table != NULL) {
				char* output_ext_file_name = file_add_extension(argv[iterator], "ext");
				FILE *output_ext_file = fopen(output_ext_file_name, "w");

				// Go over all extern refs table
				// For each ref, check that it exists, and write it in the file

				fclose(output_ext_file);
				free(output_ext_file_name);
			}
		}

		if (DEBUG_MODE) {
			printf("%s\n", state.failed ? "Fail!" : "Success!");
		}

		all_success *= 1 - state.failed;

	}

	return 1 - all_success;
}