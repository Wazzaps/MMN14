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
    {"reg",     "r%{int}"},\
    {"const",       "#%{int}"},\
    {"matdef",      "[%{int}][%{int}]"},\
    {"mataccess",   "%{word}[%{reg}][%{reg}]"},\
    {"label",       "%{word}"},\
    {"arg",     "%{reg|const|mataccess|label}"},\
    {"arg_noconst", "%{reg|mataccess|label}"},\
\
    /* Assembly directives */\
    {"data",    "%c{int}"},\
    {"string",      "\"%{word}\""},\
    {"mat",     "%{matdef}%c{int}"},\
    {"entry",       "%{word}"},\
    {"extern",      "%{word}"},\
\
    /* Ops */\
    {"mov",     "%{arg},%{arg_noconst}"},\
    {"cmp",     "%{arg},%{arg}"},\
    {"add",     "%{arg},%{arg_noconst}"},\
    {"sub",     "%{arg},%{arg_noconst}"},\
    {"not",     "%{arg_noconst}"},\
    {"clr",     "%{arg_noconst}"},\
    {"lea",     "%{mataccess|label},%{arg_noconst}"},\
    {"inc",     "%{arg_noconst}"},\
    {"dec",     "%{arg_noconst}"},\
    {"jmp",     "%{arg_noconst}"},\
    {"bne",     "%{arg_noconst}"},\
    {"red",     "%{arg_noconst}"},\
    {"prn",     "%{arg}"},\
    {"jsr",     "%{arg_noconst}"},\
    {"rts",     ""},\
    {"stop",    ""}\
};

#define PARSER_CUSTOM_TYPES_LENGTH 28


#endif //GENERAL_PARSING_H
