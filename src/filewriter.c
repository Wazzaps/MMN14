#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infinitestructures.h"
#include "utilityfunctions.h"
#include "errors.h"
#include "conststrings.h"
#include "filewriter.h"

void write_file (char* _folder_name, char* _file_name, char* extension, infstring* contents) {
	infstring* path = from_cstring(_folder_name);
	infstring* file_name = from_cstring(_file_name);
	FILE* f;

	string_concat(file_name, from_cstring(extension));

	/* If folder name empty then select current directory */
	if (path->length == 0) {
		string_concat(path, from_cstring("./"));
	}

	/* If folder name does not end with a slash add one */
	if (INF_LAST_CHAR(path) != '/' && INF_LAST_CHAR(path) != '\\') {
		string_append_char(path, '/');
	}

	/* Write the data */
	string_concat(path, file_name);
	f = fopen(to_cstring(path), "w");
	if (!f) {
    	printf(STR_ERR_ERROR_OPENING_FILE_FOR_WRITING, _file_name, extension);
    	exit(ERROR_FILEWRITE);
	} else {
		fprintf(f, "%s", to_cstring(contents));
		fclose(f);
	}
}