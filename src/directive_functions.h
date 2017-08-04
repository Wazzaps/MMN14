//
// Created by david on 7/4/17.
//

#ifndef INDIVIDUAL_DIRECTIVES_AND_OPS_H
#define INDIVIDUAL_DIRECTIVES_AND_OPS_H

#include "structures.h"

#define ASSEMBLER_DIRECTIVE_LIST_LENGTH 5
#define ASSEMBLER_DIRECTIVE_LIST {"data", "string", "mat", "entry", "extern"}

#define DECL_SIGNATURE void* parse_struct, struct assembler_state_tables* tables, char* label_name

typedef struct {
	char* name;

	int (* func) (DECL_SIGNATURE);
} decl_t;

int decl_data (DECL_SIGNATURE);

int decl_string (DECL_SIGNATURE);

int decl_mat (DECL_SIGNATURE);

int decl_entry (DECL_SIGNATURE);

int decl_extern (DECL_SIGNATURE);


#endif //INDIVIDUAL_DIRECTIVES_AND_OPS_H
