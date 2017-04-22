#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argmanager.h"
#include "conststrings.h"
#include "errors.h"

program_arguments argmanager_process (int argc, char *argv[]) {
	int i;
	unsigned int file_count = 0;
	program_arguments output;
	
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
				}
				printf(STR_INF_SELECTED_OUTPUT_FOLDER, argv[++i]);
			} else if (!strcmp(argv[i], FLAG_HELP) || !strcmp(argv[i], FLAG_HELP_SHORT)) {
				/* Help */
				printf(STR_INF_PROG_USAGE);
				return output;
			} else {
				printf("Unknown flag: %s\n", argv[i]);
				exit(UNKNOWN_FLAG);
			}
		} else {
			printf("File: %s\n", argv[i]);
			file_count++;
		}
	}

	if (file_count == 0 && output.should_compile) {
		printf(STR_ERR_MISSING_ARGUMENTS STR_INF_PROG_USAGE);
		exit(MISSING_INPUT_FILES);
	}

	putchar('\n');
	return output;
}