#include <string.h>
#include <stdlib.h>
#include "whitespace.h"
#include "infinitestructures.h"


char* whitespace_process (char* code) {
	char* output;
	output = _whitespace_firstpass(code);

	return output;
}

/* First pass: Switch all \r\n to just \n by removing \r */
char* _whitespace_firstpass (char* code) {
	char* output = malloc(1);
	int codelen = strlen(code);
	int i;
	
	/* Loop over every char */
	for (i = 0; i < codelen; i++) {
		if (code[i] != '\r') {
			string_append_char(&output, code[i]);
		}
	}

	return output;
}