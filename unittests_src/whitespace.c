#include <stdio.h>
#include "../src/whitespace.h"
#include <assert.h>
#include <string.h>

int main () {
	char* mystring = "\t\tHello\r\n   world!\r\nYep!";

	/** _whitespace_firstpass **/
	mystring = _whitespace_firstpass(mystring);
	assert(!strcmp(mystring, "\t\tHello\n   world!\nYep!"));

	/** _whitespace_secondpass **/
	mystring = _whitespace_secondpass(mystring);
	assert(!strcmp(mystring, "Hello\nworld!\nYep!"));
	
    return 0;
}