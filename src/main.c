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
	int i;
	program_arguments args = argmanager_process(argc, argv);

	char* input_folder = args.input_folder ? args.input_folder_name : "";
	/*char* output_folder = args.output_folder ? args.output_folder_name : "";*/

	/* Print selected input and output folders */
	if (args.input_folder && args.verbose) {
		printf(STR_INF_SELECTED_INPUT_FOLDER, args.input_folder_name);
	}

	if (args.output_folder && args.verbose) {
		printf(STR_INF_SELECTED_OUTPUT_FOLDER, args.output_folder_name);
	}

	/* Load all files provided by arguments */
	for (i = 0; i < args.file_count; i++) {
		if (args.verbose) {
			printf("Loading file: %s\n", args.files[i].file_name);
		}
		args.files[i].contents = load_file(input_folder, args.files[i].file_name);
		
	}

	/* TODO: Process whitespace */
	for (i = 0; i < args.file_count; i++) {
		
	}

	/* TODO: Split each file into a line array */

	/* TODO: Group each file's lines by type (assembler directive / assembly instruction) */

	/* TODO: Check validity of each assembler directive */

	/* TODO: Tokenize assembly instructions */

	/* TODO: Check validity of each instruction */

	/* TODO: Replace token representation with a representation
	   more resembling of the machine code */

	/* TODO: Create a symbol table from assembler directives */

	/* TODO: Replace each symbol token with it's address */

	/* TODO: Create array of machine code in normal base */
	
	/* TODO: Convert bases and output as strings */

	/* TODO: Write the object file */

	/* TODO: Create a list of all extern assembler directives */

	/* TODO: Write extern file */

	/* TODO: Create a list of all entry assembler directives */

	/* TODO: Write entry file */

	return 0;
}
