#include <stdio.h>
#include "../src/infinitestructures.h"
#include <assert.h>
#include <string.h>

int main () {
	/** Infinite strings **/
	/* Concat */
	char* result;
	result = string_concat("hello ", "world");
    
	assert(!strcmp(result, "hello world"));
	assert(strlen(result) == 11);

	/* Expand */
	result = string_expand_by(result, 2);
	result[11] = '!';
	result[12] = '!';
	
	assert(!strcmp(result, "hello world!!"));
	assert(strlen(result) == 13);

	/* Append char */
	string_append_char(&result, '!');
	
	assert(!strcmp(result, "hello world!!!"));
	assert(strlen(result) == 14);

    return 0;
}