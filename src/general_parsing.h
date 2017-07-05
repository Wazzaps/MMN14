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
        {"reg",         "r%{int}"},\
        {"const",       "#%{int}"},\
        {"matdef",      "[%{int}][%{int}]"},\
        {"mataccess",   "%{word}[%{int}][%{int}]"},\
        {"label",       "%{word}"},\
        {"arg",         "%{reg|const|mataccess|label}"},\
        {"arg_noconst", "%{reg|mataccess|label}"},\
\
        /* Assembly directives */\
        {"data",        "%a{int}"},\
        {"string",      "\"%{word}\""},\
        {"mat",         "%{matdef} %ac{int}"},\
        {"entry",       "%{word}"},\
        {"extern",      "%{word}"},\
\
        /* Ops */\
        {"mov",         "%{arg},%{arg_noconst}"},\
        {"cmp",         "%{arg},%{arg}"},\
        {"add",         "%{arg},%{arg_noconst}"},\
        {"sub",         "%{arg},%{arg_noconst}"},\
        {"not",         "%{arg_noconst}"},\
        {"clr",         "%{arg_noconst}"},\
        {"lea",         "%{mataccess|label},%{arg_noconst}"},\
        {"inc",         "%{arg_noconst}"},\
        {"dec",         "%{arg_noconst}"},\
        {"jmp",         "%{arg_noconst}"},\
        {"bne",         "%{arg_noconst}"},\
        {"red",         "%{arg_noconst}"},\
        {"prn",         "%{arg}"},\
        {"jsr",         "%{arg_noconst}"},\
        {"rts",         ""},\
        {"stop",        ""}\
};\


#endif //GENERAL_PARSING_H
