//
// Created by david on 6/17/17.
//

#include <string.h>
#include <ctype.h>
#include "structures.h"
#include "util_functions.h"
#include "errors.h"
#include "string_parser.h"
#include "general_parsing.h"

parser_definition custom_types[] = {
        {"reg",         "r%{int}"},
        {"const",       "#%{int}"},
        {"matdef",      "[%{int}][%{int}]"},
        {"mataccess",   "%{word}[%{int}][%{int}]"},
        {"label",       "%{word}"},
        {"arg",         "%{reg|const|mataccess|label}"},
        {"arg_noconst", "%{reg|mataccess|label}"},

        /* Assembly directives */
        {"data",        "%a{int}"},
        {"string",      "\"%{word}\""},
        {"mat",         "%{matdef} %ac{int}"},
        {"entry",       "%{word}"},
        {"extern",      "%{word}"},

        /* Ops */
        {"mov",         "%{arg},%{arg_noconst}"},
        {"cmp",         "%{arg},%{arg}"},
        {"add",         "%{arg},%{arg_noconst}"},
        {"sub",         "%{arg},%{arg_noconst}"},
        {"not",         "%{arg_noconst}"},
        {"clr",         "%{arg_noconst}"},
        {"lea",         "%{mataccess|label},%{arg_noconst}"},
        {"inc",         "%{arg_noconst}"},
        {"dec",         "%{arg_noconst}"},
        {"jmp",         "%{arg_noconst}"},
        {"bne",         "%{arg_noconst}"},
        {"red",         "%{arg_noconst}"},
        {"prn",         "%{arg}"},
        {"jsr",         "%{arg_noconst}"},
        {"rts",         ""},
        {"stop",        ""}
};

/* Reads assembly directives */
void parse_directives(FILE *fp, string file_name, entry_list *entry_table,
                      extern_list *extern_table, label_list *label_table) {
    string line;
    int line_num = 1;
    int line_length = 0;

    /* Read each line for pass 1 (assembly directives) */
    while ((line_length = get_line(line, MAX_STRING_LENGTH+1, fp)) != -1) {
        char* code_contents;
        char* label_name;

        /* Check that line length isn't over the limit */
        if (line_length == MAX_STRING_LENGTH) {
            fprintf(stderr, ERROR_LINE_TOO_LONG, line_num, file_name, MAX_STRING_LENGTH);
        }

        clean_and_preprocess_line(line, &label_name, &code_contents, line_num);

        if (label_name != NULL && strlen(label_name) > MAX_LABEL_NAME_LENGTH) {
            fprintf(stderr, ERROR_LABEL_TOO_LONG, MAX_LABEL_NAME_LENGTH, line_num);
        }

        if (label_name != NULL && code_contents[0] == '\0') {
            fprintf(stderr, ERROR_USELESS_LABEL, line_num);
        }

        if (code_contents[0] == '.') {
            char* original_code_contents = code_contents;
            if (isblank(code_contents[1])) {
                fprintf(stderr, ERROR_WHITESPACE_BEFORE_DIRECTIVE, line_num);
                code_contents = advance_whitespace(code_contents+1) - 1;
                *code_contents = '.';
            }

        }

        if (DEBUG_MODE && code_contents[0] != '\0') {
            printf("[%3d]  %c  %s: %s\n", line_num,
                   code_contents[0] == '.' ? 'D' : 'C',
                   label_name, code_contents);
        }

        line_num++;
    }
}