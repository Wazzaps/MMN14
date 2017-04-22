#include <stdio.h>
#include "../src/whitespace.h"
#include <assert.h>
#include <string.h>

int main () {
	char* mystring = "Hello\r\nworld!";
	
	/** _whitespace_firstpass **/
	assert(!strcmp(_whitespace_firstpass(mystring), "Hello\nworld!"));
    return 0;
}