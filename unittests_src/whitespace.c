#include <stdio.h>
#include "../src/whitespace.h"
#include <assert.h>
#include <string.h>

int main () {
	infstring* mystring = from_cstring("\t\tHello\r\n   world!\r\n ; Testing!");

	/** _whitespace_firstpass **/
	mystring = _whitespace_firstpass(mystring);
	assert(!strcmp(to_cstring(mystring), "\t\tHello\n   world!\n ; Testing!"));

	/** _whitespace_secondpass **/
	mystring = _whitespace_secondpass(mystring);
	assert(!strcmp(to_cstring(mystring), "Hello\nworld!\n; Testing!"));

	/** _whitespace_thirdpass **/
	mystring = _whitespace_thirdpass(mystring);
	assert(!strcmp(to_cstring(mystring), "Hello\nworld!\n"));
	
    return 0;
}