#include <stdio.h>
#include "../src/filewriter.h"
#include "../src/fileloader.h"
#include <assert.h>
#include <string.h>

int main () {
	single_file myfile;
	
	/** write_file **/
	write_file("integrationtests/temp/", "writetest", ".as", "abc");

	/** load_file **/
	myfile = load_file("integrationtests/temp/", "writetest");

	assert(!strcmp(myfile.contents, "abc"));
	assert(!strcmp(myfile.file_name, "writetest"));
    return 0;
}