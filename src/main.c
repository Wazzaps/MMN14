#include <stdio.h>
#include "argmanager.h"


int main(int argc, char *argv[]) {
	/* Handle arguments */
	program_arguments output = argmanager_process(argc, argv);
	int i;

	for (i = 0; i < output.files_count; i++) {
		printf("File: %s\n", output.files[i]);
	}

	return 0;
}
