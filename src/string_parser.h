#ifndef STRING_PARSER_H
#define STRING_PARSER_H

#include "structures.h"
#include <stdarg.h>

typedef struct {
    string name;
    string arguments;
} parser_definition;

int myscanf(string format,
            parser_definition custom_types[],
            int custom_types_length,
            parser_definition searchables[],
            int searchables_length,
            string input, ...);

#endif //STRING_PARSER_H
