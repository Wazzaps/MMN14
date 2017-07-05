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