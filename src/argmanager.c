#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infinitestructures.h"
#include "argmanager.h"
#include "conststrings.h"
#include "errors.h"

program_arguments argmanager_process (int argc, char *argv[]) {
	int i;
	program_arguments output;
	
	/* 128 (MAX_FILE_COUNT) files should be enough */
	output.files = calloc(MAX_FILE_COUNT, sizeof(single_file)); 

	/*if (i == argc - 1 || argv[i+1][0] == '-') {
					printf(STR_ERR_MISSING_FLAG_ARGUMENTS, argv[i]);
					exit(MISSING_FLAG_ARGUMENT);
				} else {
					output.input_folder_name = argv[++i];
					output.input_folder = 1;
				}
	  Loop over arguments, skipping over index 0 because
	  it's the exexutable name and that's not important
	*/
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
				/* Input folder */
				if (i == argc - 1 || argv[i+1][0] == '-') {
					printf(STR_ERR_MISSING_FLAG_ARGUMENTS, argv[i]);
					exit(MISSING_FLAG_ARGUMENT);
				} else {
					output.input_folder_name = argv[++i];
					output.input_folder = 1;
				}
			} else if (!strcmp(argv[i], FLAG_VERBOSE) || !strcmp(argv[i], FLAG_VERBOSE_SHORT)) {
				/* Verbose messages (debugging) */
				output.verbose = 1;
			} else if (!strcmp(argv[i], FLAG_HELP) || !strcmp(argv[i], FLAG_HELP_SHORT)) {
				/* Help */
				printf(STR_INF_PROG_USAGE);
				exit(NO_ERROR);
			} else {
				printf("Unknown flag: %s\n", argv[i]);
				exit(UNKNOWN_FLAG);
			}
		} else {
			/* Add file to file list */
			if (output.file_count < MAX_FILE_COUNT) {
				output.files[output.file_count].file_name = argv[i];
				output.file_count++;
			} else {
				printf(STR_ERR_MAX_FILES_REACHED, MAX_FILE_COUNT);
			}
		}
	}

	/* Check if there are any files have been passed */
	if (output.file_count == 0) {
		printf(STR_ERR_MISSING_ARGUMENTS STR_INF_PROG_USAGE);
		exit(MISSING_INPUT_FILES);
	}

	return output;
}