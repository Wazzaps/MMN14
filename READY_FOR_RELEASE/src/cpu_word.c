#include <stdlib.h>
#include <stdio.h>
#include "cpu_word.h"
#include "errors.h"

#define realloc_block_size 25

unsigned add_word (cpu_word** block, unsigned* counter, cpu_word data) {
	/* Basically we only jump in modulos of the block size */
	unsigned old_size = (*counter + realloc_block_size - 1) / realloc_block_size * realloc_block_size;
	unsigned new_size = (*counter + realloc_block_size) / realloc_block_size * realloc_block_size;

	if (old_size != new_size)
		*block = realloc(*block, new_size * sizeof(cpu_word));
	if (!*block) {
		fprintf(stderr, ERROR_OUT_OF_MEMORY);
		exit(1);
	}

	(*block)[*counter] = data;
	return (*counter)++;
}