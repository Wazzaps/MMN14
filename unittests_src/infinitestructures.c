#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../src/infinitestructures.h"

int main () {
	int i;
	int j = 0;
	infstring* result1;
	infstring* result2;
	infstring* result3;

	/** Infinite strings **/
	/* string_new, string_append_char, string_length, to_cstring */
	result1 = string_new();
	for (i = 0; i < 10; i++) {
		string_append_char(result1, 'a');
	}
	assert(string_length(result1) == 10);
	assert(!strcmp(to_cstring(result1), "aaaaaaaaaa"));

	/* string_append_to_last */
	string_append_to_last(result1->next_element, 'b');
	assert(string_length(result1) == 11);
	assert(!strcmp(to_cstring(result1), "aaaaaaaaaab"));

	/* from_cstring */
	result2 = from_cstring("cdef");
	
	/* string_concat */
	string_concat(result1, result2);
	assert(string_length(result1) == 15);
	assert(!strcmp(to_cstring(result1), "aaaaaaaaaabcdef"));

	/* string_get_char */
	assert(string_get_char(result1, 1) == 'a');

	assert(string_get_char(result1, 7) == 'a');
	assert(string_get_char(result1, 8) == 'a');
	assert(string_get_char(result1, 9) == 'a');

	assert(string_get_char(result1, 14) == 'f');
	assert(string_get_char(result1, 15) == '\0');
	assert(string_get_char(result1, 500) == '\0');

	/* string_get_next_char */
	result3 = string_new();
	for (i = 0; i < 26; i++) {
		string_append_char(result3, 'a'+i);
	}

	for (i = 0; i < 26; i++) {
		assert(string_get_next_char(&result3, &j) == 'a'+i);
	}

    return 0;
}