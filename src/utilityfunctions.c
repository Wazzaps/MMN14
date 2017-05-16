#include <string.h>
#include <string.h>
#include <stdlib.h>
#include "utilityfunctions.h"

char* strdup (char* src) {
	int length = strlen(src)+1;
	char* output = malloc(length);
	memcpy(output, src, length);
	return output;
}