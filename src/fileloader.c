#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "infinitestructures.h"
#include "utilityfunctions.h"
#include "errors.h"
#include "conststrings.h"
#include "fileloader.h"

infstring* load_file (char* _folder_name, char* _file_name) {
	infstring* path = from_cstring(_folder_name);
	infstring* file_name = from_cstring(_file_name);
	FILE* f;

	infstring* contents = calloc(1, sizeof(infstring));
	infstring* current = contents;

	string_concat(file_name, from_cstring(ASM_EXTENSION));

	/* If folder name empty then select current directory */
	if (path->length == 0) {
		string_concat(path, from_cstring("./"));
	}

	/* If folder name does not end with a slash add one */
	if (INF_LAST_CHAR(path) != '/' && INF_LAST_CHAR(path) != '\\') {
		string_append_char(path, '/');
	}

	/* Open the file */
	string_concat(path, file_name);

	f = fopen(to_cstring(path), "r");
	if (f == NULL) {
    	printf(STR_ERR_ERROR_OPENING_FILE_FOR_READING, _file_name, ASM_EXTENSION);
    	exit(ERROR_FILEREAD);
	}

	/* Copy char by char the file to the string */
	while (1) {
		char last_char = fgetc(f);
		if (last_char == EOF) {
			break;
		}
		current = string_append_to_last(current, last_char);
	}

	fclose(f);

	return contents;
}