#include <stdlib.h>
#include "structures.h"

code_table create_code_table () {
	code_table result;
	result.data = malloc(0);
	result.length = 0;
	return result;
}