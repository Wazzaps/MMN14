#include <stdio.h>
#include <stdlib.h>
#include "argmanager.h"
#include "fileloader.h"
#include "infinitestructures.h"
#include "filewriter.h"
#include "conststrings.h"
#include "whitespace.h"


int main(int argc, char *argv[]) {
	/* Handle arguments */
	program_arguments arguments = argmanager_process(argc, argv);
	single_file* files = malloc(sizeof(single_file) * arguments.files_count);
	int i;

	/* Print selected input and output folders */
	if (arguments.input_folder) {
		printf(STR_INF_SELECTED_INPUT_FOLDER, arguments.input_folder_name);
	}

	if (arguments.output_folder) {
		printf(STR_INF_SELECTED_OUTPUT_FOLDER, arguments.output_folder_name);
	}

	/* Load all files provided by arguments */
	for (i = 0; i < arguments.files_count; i++) {
		char* input_folder = arguments.input_folder ? arguments.input_folder_name : "";
		char* output_folder = arguments.output_folder ? arguments.output_folder_name : "";
		printf("File: %s\n", arguments.files[i]);
		files[i] = load_file(input_folder, arguments.files[i]);
		/*printf((*(files + i * sizeof(single_file))).contents);*/
		write_file(output_folder, arguments.files[i], ".ob", whitespace_process((*(files + i * sizeof(single_file))).contents));
	}

	return 0;
}
