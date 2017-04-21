#include <stdio.h>
#include "argmanager.h"


int main(int argc, char *argv[]) {
	/* Handle arguments */
	program_arguments output = argmanager_process(argc, argv);
	if (output.error) {
		return output.error;
	}
	return 0;
}
