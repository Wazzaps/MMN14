#ifndef OP_PARSER_H
#define OP_PARSER_H

#include <stdio.h>
#include "structures.h"

typedef struct {
	char* name;
	int number_of_args;
	char* format;
} op_t;

#define OP_LIST_LENGTH 16

int parse_ops (FILE* fp, string file_name, struct assembler_state_tables*);

#endif //OP_PARSER_H
