#include "constant_data.h"
#include "parse_directives.h"

op_t OPS[OPS_LENGTH] = {
        {"mov",  2, CONST|LABEL|MATRX|REGIS, LABEL|MATRX|REGIS},
        {"cmp",  2, CONST|LABEL|MATRX|REGIS, CONST|LABEL|MATRX|REGIS},
        {"add",  2, CONST|LABEL|MATRX|REGIS, LABEL|MATRX|REGIS},
        {"sub",  2, CONST|LABEL|MATRX|REGIS, LABEL|MATRX|REGIS},
        {"not",  1, LABEL|MATRX|REGIS,       NONE},
        {"clr",  1, LABEL|MATRX|REGIS,       NONE},
        {"lea",  2, LABEL | MATRX,           LABEL | MATRX | REGIS},
        {"inc",  1, LABEL|MATRX|REGIS,       NONE},
        {"dec",  1, LABEL|MATRX|REGIS,       NONE},
        {"jmp",  1, LABEL|MATRX|REGIS,       NONE},
        {"bne",  1, LABEL|MATRX|REGIS,       NONE},
        {"red",  1, LABEL|MATRX|REGIS,       NONE},
        {"prn",  1, CONST|LABEL|MATRX|REGIS, NONE},
        {"jsr",  1, LABEL|MATRX|REGIS,       NONE},
        {"rts",  0, NONE,                    NONE},
        {"stop", 0, NONE,                    NONE}
};

direc_t DIRECTIVES[DIRECTIVES_LENGTH] = {
		{"data", &direc_data},
		{"string", &direc_string},
		{"mat", &direc_mat},
		{"entry", &direc_entry},
		{"extern", &direc_extern}
};