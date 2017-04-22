#ifndef ARGMANAGER_H 
#define ARGMANAGER_H 

#include "errors.h"

#define FLAG_OUTPUT_FOLDER "--outputfolder"
#define FLAG_OUTPUT_FOLDER_SHORT "-o"
#define FLAG_HELP "--help"
#define FLAG_HELP_SHORT "-h"

typedef struct program_arguments_struct {
	/* Files */
	int files_count;
	char** files;

	/* Flags */
	unsigned int output_folder : 1;
	unsigned int should_compile : 1;
	
	/* Flag arguments */
	char* output_folder_name;

	/* Error */
	errorcode error;
} program_arguments;

program_arguments argmanager_process (int argc, char *argv[]);

#endif