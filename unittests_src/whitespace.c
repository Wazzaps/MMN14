#include <stdio.h>
#include "../src/whitespace.h"
#include <assert.h>
#include <string.h>

int main () {
	char* mystring = "\t\tHello\r\n   world!\r\n ; Testing!";

	/** _whitespace_firstpass **/
	mystring = _whitespace_firstpass(mystring);
	assert(!strcmp(mystring, "\t\tHello\n   world!\n ; Testing!"));

	/** _whitespace_secondpass **/
	mystring = _whitespace_secondpass(mystring);
	assert(!strcmp(mystring, "Hello\nworld!\n; Testing!"));

	/** _whitespace_thirdpass **/
	mystring = _whitespace_thirdpass(mystring);
	assert(!strcmp(mystring, "Hello\nworld!\n"));
	
    return 0;
}