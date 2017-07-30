#include <string.h>
#include <stdlib.h>
#include "util_functions.h"

/* Gets a line from a file stream, until a length is
 * reached, then skip to next line. (supports \r\n) */
int get_line (char* buffer, int length, FILE* stream) {
	int last_char = fgetc(stream);
	int input_length = 0;

	while (last_char != EOF && last_char != '\n' && last_char != '\r') {
		/* Slide to end of line if reached end of buffer */
		if (input_length == length - 1) {
			last_char = fgetc(stream);
			continue;
		}
		buffer[input_length++] = (char) last_char;
		last_char = fgetc(stream);
	}

	buffer[input_length] = '\0';

	/* Check for /r/n */
	if (last_char == '\r') {
		last_char = fgetc(stream);
		if (last_char != '\n') {
			ungetc(last_char, stream);
		}
	}

	return last_char == EOF && input_length == 0 ? -1 : input_length;
}

/* Converts a positive int to "Weird" base 4 */
char* to_base4 (unsigned int input) {
	char* output = calloc(20, 1);
	char* output_reversed = calloc(20, 1);
	char* out_ptr = output_reversed;
	int i;
	int len;

	while (input != 0) {
		*out_ptr = (char) ((input % 4) + 'a');
		input /= 4;
		out_ptr++;
	}

	len = (int) strlen(output_reversed);

	for (i = 0; i < len; i++) {
		output[i] = output_reversed[len - i - 1];
	}

	return output;
}