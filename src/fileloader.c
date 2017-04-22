#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "infinitestructures.h"
#include "utilityfunctions.h"
#include "errors.h"
#include "conststrings.h"
#include "fileloader.h"

char* load_file (char* _folder_name, char* file_name) {
	char* folder_name = string_copy(_folder_name);
	char* path = string_concat(file_name, ASM_EXTENSION);
	FILE* f;
	char* contents;
	long int file_size;
	long int i = 0;

	/* If folder name empty then select current directory */
	if (strlen(folder_name) == 0) {
		free(folder_name);
		folder_name = "./";
	}

	/* If folder name does not end with a slash add one */
	if (string_get_last_char(folder_name) != '/' && string_get_last_char(folder_name) != '\\') {
		string_append_char(&folder_name, '/');
	}

	/* Open the file */
	path = string_concat(folder_name, path);

	f = fopen(path, "r");
	if (f == NULL) {
    	printf(STR_ERR_ERROR_OPENING_FILE_FOR_READING, file_name, ASM_EXTENSION);
    	exit(ERROR_FILEREAD);
	}

	/* Get the file's size */
	fseek(f, 0L, SEEK_END);
	file_size = ftell(f);
	rewind(f);
	contents = malloc(file_size);

	/* Copy char by char the file to the string */
	for (i = 0; i < file_size; i++) {
		contents[i] = fgetc(f);
	}

	fclose(f);

	return contents;
}