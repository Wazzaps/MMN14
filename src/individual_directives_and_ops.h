//
// Created by david on 7/4/17.
//

#ifndef INDIVIDUAL_DIRECTIVES_AND_OPS_H
#define INDIVIDUAL_DIRECTIVES_AND_OPS_H

#include "structures.h"

#define ASSEMBLER_DIRECTIVE_LIST_LENGTH 5
#define ASSEMBLER_OP_LIST_LENGTH 2

#define OP_SIGNATURE void* parse_struct, struct assembler_state_tables* tables, unsigned int line_num,\
    char* label_name

typedef struct {
	char* name;

	int (* func) (OP_SIGNATURE);
} op;

#define OP(OP_NAME) {#OP_NAME, &op_ ## OP_NAME}
#define OP_DECLARATION(OP_NAME) int op_ ## OP_NAME(OP_SIGNATURE)

OP_DECLARATION(data);
OP_DECLARATION(string);
OP_DECLARATION(mat);
OP_DECLARATION(entry);
OP_DECLARATION(extern);

OP_DECLARATION(mov);
OP_DECLARATION(cmp);
OP_DECLARATION(add);
OP_DECLARATION(sub);
OP_DECLARATION(not);
OP_DECLARATION(clr);
OP_DECLARATION(lea);
OP_DECLARATION(inc);
OP_DECLARATION(dec);
OP_DECLARATION(jmp);
OP_DECLARATION(bne);
OP_DECLARATION(red);
OP_DECLARATION(prn);
OP_DECLARATION(jsr);
OP_DECLARATION(rts);
OP_DECLARATION(stop);


#endif //INDIVIDUAL_DIRECTIVES_AND_OPS_H
