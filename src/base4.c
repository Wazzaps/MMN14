#include <stdlib.h>
#include "base4.h"

char* tobase4(cpu_word word, int min_size) {
	int size = 0;
	int max_size = 0;
	char* output;
	cpu_word temp = word;
	int i;

	char base4_map[] = {'a', 'b', 'c', 'd'};

	// Calculate number of characters
	while (temp != 0) {
		temp = temp >> 2;
		size++;
	}

	// Actual number of characters = max(size, min_size)
	max_size = (size < min_size ? min_size : size);

	output = malloc((size_t) (max_size + 1));
	temp = word;

	// Put all data
	for (i = max_size-1; i >= max_size - size; i--) {
		output[i] = base4_map[temp & 3];
		temp = temp >> 2;
	}

	// Put the padding 'a's
	for (i = 0; i < min_size - size; i++) {
		output[i] = 'a';
	}

	output[max_size] = '\0';

	return output;
}
