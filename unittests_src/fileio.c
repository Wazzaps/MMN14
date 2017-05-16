#include <stdio.h>
#include "../src/filewriter.h"
#include "../src/fileloader.h"
#include "../src/infinitestructures.h"
#include <assert.h>
#include <string.h>

int main () {
	infstring* myfilecontents;
	
	/** write_file **/
	write_file("integrationtests/temp/", "writetest", ".as", from_cstring("abc"));

	/** load_file **/
	myfilecontents = load_file("integrationtests/temp/", "writetest");

	assert(!strcmp(to_cstring(myfilecontents), "abc"));
    return 0;
}