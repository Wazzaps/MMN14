#ifndef STRING_PARSER_H
#define STRING_PARSER_H

#include "structures.h"
#include <stdarg.h>

typedef struct {
	string name;
	string format;
} parser_definition;

void* mysscanf (string format, int custom_types_length, parser_definition custom_types[], char* input,
                int fail_on_excessive_text);

#define _PARSER_GET_TYPE(ptr, type) (*((type*)(((ptr) += sizeof(type))-sizeof(type))))
#define PARSER_GET_INT(ptr) _PARSER_GET_TYPE((ptr), int)
#define PARSER_GET_CHAR(ptr) _PARSER_GET_TYPE((ptr), char)

#endif //STRING_PARSER_H
