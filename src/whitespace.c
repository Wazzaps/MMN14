#include <string.h>
#include <stdlib.h>
#include "whitespace.h"
#include "infinitestructures.h"


char* whitespace_process (char* code) {
	char* output;
	output = _whitespace_firstpass(code);
	output = _whitespace_secondpass(output);
	output = _whitespace_thirdpass(output);/**/

	return output;
}

/* First pass: Switch all \r\n to just \n by removing \r */
char* _whitespace_firstpass (char* code) {
	char* output = malloc(1);
	output[0] = 0;
	int codelen = strlen(code);
	int i;
	
	/* Loop over every char */
	for (i = 0; i < codelen; i++) {
		if (code[i] != '\r') {
			output = string_append_char(output, code[i]);
		}
	}

	return output;
}

/* Second pass: Remove all whitespace from starts of lines */
char* _whitespace_secondpass (char* code) {
	char* output = malloc(1);
	output[0] = 0;
	int codelen = strlen(code);
	int i;
	int is_at_start = 1;
	
	/* Loop over every char */
	for (i = 0; i < codelen; i++) {
		if (!is_at_start || (code[i] != ' ' && code[i] != '\t' && code[i] != '\n')) {
			output = string_append_char(output, code[i]);
			is_at_start = 0;
		}
		if (code[i] == '\n') {
			is_at_start = 1;
		}
	}

	return output;
}

/* Third pass: Remove all comments */
char* _whitespace_thirdpass (char* code) {
	char* output = malloc(1);
	output[0] = 0;
	int codelen = strlen(code);
	int i;
	int is_in_comment = 0;
	int is_in_string = 0;
	
	/* Loop over every char */
	for (i = 0; i < codelen; i++) {
		if (code[i] == '\"' && !is_in_comment) {
			is_in_string = !is_in_string;
		}
		if (code[i] == ';' && !is_in_string) {
			is_in_comment = 1;
		}
		if (code[i] == '\n') {
			is_in_comment = 0;
			is_in_string = 0;
		}

		if (!is_in_comment) {
			output = string_append_char(output, code[i]);
		}
	}

	return output;
}