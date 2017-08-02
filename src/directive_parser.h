#ifndef DIRECTIVE_PARSER_H
#define DIRECTIVE_PARSER_H

#include <stdio.h>
#include "structures.h"

int parse_directives_and_labels (FILE* fp, string file_name, struct assembler_state_tables*);

#endif //DIRECTIVE_PARSER_H
