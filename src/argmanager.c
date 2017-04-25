#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infinitestructures.h"
#include "argmanager.h"
#include "conststrings.h"
#include "errors.h"

program_arguments argmanager_process (int argc, char *argv[]) {
	int i;
	unsigned int file_count = 0;
	program_arguments output;
	char** files = malloc(sizeof(char*));
	
	output.should_compile = 1;

	if (argc == 1) {
		printf(STR_ERR_MISSING_ARGUMENTS STR_INF_PROG_USAGE);
		exit(MISSING_INPUT_FILES);
	}

	for (i = 1; i < argc; i++) {
		/* If the argument word starts with a dash it's a flag */
		if (argv[i][0] == '-') {
			if (!strcmp(argv[i], FLAG_OUTPUT_FOLDER) || !strcmp(argv[i], FLAG_OUTPUT_FOLDER_SHORT)) {
				/* Output folder */
				if (i == argc - 1 || argv[i+1][0] == '-') {
					printf(STR_ERR_MISSING_FLAG_ARGUMENTS, argv[i]);
					exit(MISSING_FLAG_ARGUMENT);
				} else {
					output.output_folder_name = argv[++i];
					output.output_folder = 1;
				}
			} else if (!strcmp(argv[i], FLAG_INPUT_FOLDER) || !strcmp(argv[i], FLAG_INPUT_FOLDER_SHORT)) {
				/* Output folder */
				if (i == argc - 1 || argv[i+1][0] == '-') {
					printf(STR_ERR_MISSING_FLAG_ARGUMENTS, argv[i]);
					exit(MISSING_FLAG_ARGUMENT);
				} else {
					output.input_folder_name = argv[++i];
					output.input_folder = 1;
				}
			} else if (!strcmp(argv[i], FLAG_HELP) || !strcmp(argv[i], FLAG_HELP_SHORT)) {
				/* Help */
				printf(STR_INF_PROG_USAGE);
				exit(NO_ERROR);
			} else {
				printf("Unknown flag: %s\n", argv[i]);
				exit(UNKNOWN_FLAG);
			}
		} else {
			files = array_expand_to(files, (file_count + 2), sizeof(char*));
			files[file_count] = argv[i];
			file_count++;
		}
	}

	if (file_count == 0 && output.should_compile) {
		printf(STR_ERR_MISSING_ARGUMENTS STR_INF_PROG_USAGE);
		exit(MISSING_INPUT_FILES);
	}

	output.files_count = file_count;
	output.files = files;

	return output;
}