#include <stdio.h>
#include "../src/filewriter.h"
#include <assert.h>
#include <string.h>

int main () {
	/** write_file **/
	write_file("integrationtests/temp/", "writetest", ".ob", "abc");
    return 0;
}