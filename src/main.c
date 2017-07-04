#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "errors.h"
#include "string_parser.h"

int main (int argc, char* argv[]) {
    int iterator;
    int failed_file_check = 0;
    void *ptr;
    int len;
    int i;
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

    /* Check that file arguments are valid */
    if (argc == 1) {
        fprintf(stderr, ERROR_NO_INPUT_FILES);
        return 1;
    }

    for (iterator = 1; iterator < argc; iterator++) {
        string file_name = {};
        strcpy(file_name, argv[iterator]);
        strcat(file_name, ".as");
        FILE* file = fopen(file_name, "r");
        if (file == NULL) {
            fprintf(stderr, ERROR_CANNOT_READ, argv[iterator]);
            failed_file_check = 1;
        }
        fclose(file);
    }

    if (failed_file_check)
        return 1;

    /* Open files */
    for (iterator = 1; iterator < argc; iterator++) {
        string file_name = {};
        strcpy(file_name, argv[iterator]);
        strcat(file_name, ".as");
        FILE* file = fopen(file_name, "r");
        if (DEBUG_MODE) {
            printf("Opening file: %s\n", file_name);
        }

        /* Create relevant tables */
        entry_list entry_table;
        extern_list extern_table;
        label_list* label_table;
        /*data_table the_data_table;
        code_table the_code_table;*/

        //parse_directives(file, argv[iterator], &entry_table, &extern_table, label_table);

        /* Close file */
        fclose(file);
    }

    ptr = mysscanf("%{mat}", 26, custom_types, "[1][2] 1,2,3,4,5,6,7", 1);
    if (!ptr) {
        printf("Parser failed gracefully!\n");
    } else {
        int x = PARSER_GET_INT(ptr);
        int y = PARSER_GET_INT(ptr);
        printf("[%d][%d] ", x, y); // Mat x,y
        len = PARSER_GET_INT(ptr); // Mat init length
        for (i = 0; i < len; i++) {
            printf("%d, ", PARSER_GET_INT(ptr)); // Mat init value(s)
        }
    }

    return 0;
}