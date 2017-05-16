#ifndef ARGMANAGER_H 
#define ARGMANAGER_H 

#include "errors.h"
#include "fileloader.h"

#define MAX_FILE_COUNT 128

#define FLAG_OUTPUT_FOLDER "--outputfolder"
#define FLAG_OUTPUT_FOLDER_SHORT "-o"
#define FLAG_INPUT_FOLDER "--inputfolder"
#define FLAG_INPUT_FOLDER_SHORT "-i"
#define FLAG_VERBOSE "--verbose"
#define FLAG_VERBOSE_SHORT "-v"
#define FLAG_HELP "--help"
#define FLAG_HELP_SHORT "-h"

typedef struct program_arguments {
	/* Files */
	unsigned int file_count;
	single_file* files;

	/* Flags */
	unsigned int output_folder : 1;
	unsigned int input_folder : 1;
	unsigned int verbose : 1;
	
	/* Flag arguments */
	char* output_folder_name;
	char* input_folder_name;
	
} program_arguments;

program_arguments argmanager_process (int argc, char *argv[]);

#endif