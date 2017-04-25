#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infinitestructures.h"
#include "utilityfunctions.h"
#include "errors.h"
#include "conststrings.h"
#include "filewriter.h"

void write_file (char* _folder_name, char* file_name, char* extension, char* contents) {
	char* folder_name = string_copy(_folder_name);
	char* path = string_concat(file_name, extension);
	FILE* f;

	/* If folder name empty then select current directory */
	if (strlen(folder_name) == 0) {
		free(folder_name);
		folder_name = "./";
	}

	/* If folder name does not end with a slash add one */
	if (string_get_last_char(folder_name) != '/' && string_get_last_char(folder_name) != '\\') {
		folder_name = string_append_char(folder_name, '/');
	}

	/* Write the data */
	path = string_concat(folder_name, path);
	f = fopen(path, "w");
	if (f == NULL) {
    	printf(STR_ERR_ERROR_OPENING_FILE_FOR_WRITING, file_name, extension);
    	exit(ERROR_FILEWRITE);
	}
	fprintf(f, "%s", contents);
	fclose(f);
}