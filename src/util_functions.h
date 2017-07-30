#ifndef UTIL_FUNCTIONS_H
#define UTIL_FUNCTIONS_H

#include <stdio.h>
#include "structures.h"

int get_line (char* buffer, int length, FILE* stream);

char* to_base4 (unsigned int input);

#endif
