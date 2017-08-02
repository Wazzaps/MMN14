#ifndef GENERAL_PARSING_H
#define GENERAL_PARSING_H

#include "string_parser.h"

#define MAX_LABEL_NAME_LENGTH 30

char* split_label_and_code (char* line);

void remove_comment (char* line);

char* advance_whitespace (char* str);

char* block_whitespace (char* str);

void clean_and_preprocess_line (char* line, char** _label_name, char** _code_contents, int line_num);

#define PARSER_CUSTOM_TYPES {\
    {"reg",     "r%{int}", "Register"},\
    {"const",       "#%{int}", "Constant value"},\
    {"matdef",      "[%{int}][%{int}]", ""},\
    {"mataccess",   "%{word}[%{reg}][%{reg}]", "Matrix access"},\
    {"label",       "%{word}", "Label"},\
\
    /* Assembly directives */\
    {"data",    "%c{int}", "A comma seperated array of numbers"},\
    {"string",      "%{quotedstring}", "String"},\
    {"mat",     "%{matdef}%ac{int}", "Matrix definition"},\
    {"entry",       "%{word}", "Word"},\
    {"extern",      "%{word}", "Word"},\
};

#define PARSER_CUSTOM_TYPES_LENGTH 10


#endif //GENERAL_PARSING_H
