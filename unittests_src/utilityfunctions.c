#include <stdio.h>
#include "../src/utilityfunctions.h"
#include <assert.h>
#include <string.h>

int main () {
	/** Getting last char **/
	char* test1 = "Hello world!";
	assert(string_get_last_char(test1) == '!');

    return 0;
}