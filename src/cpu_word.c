#include <stdlib.h>
#include "cpu_word.h"

#define realloc_block_size 25

cpu_word* add_word(cpu_word** block, unsigned* counter, cpu_word data) {
	// Basically we only jump in modulos of the block size
	unsigned old_size = (*counter + realloc_block_size - 1) / realloc_block_size * realloc_block_size;
	unsigned new_size = (*counter + realloc_block_size) / realloc_block_size * realloc_block_size;
	if (old_size != new_size)
		*block = realloc(*block, new_size);
	(*block)[*counter] = data;
	(*counter)++;
	return (*block) + *counter - 1;
}