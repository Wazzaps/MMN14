//
// Created by david on 7/4/17.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "individual_directives_and_ops.h"
#include "string_parser.h"

/* Directives */
int op_data (OP_SIGNATURE) {

	return 0;
}

int op_string (OP_SIGNATURE) {

	return 0;
}

int op_mat (OP_SIGNATURE) {

	return 0;
}

int op_entry (OP_SIGNATURE) {
	int len = PARSER_GET_INT(parse_struct);
	ent_ext_table_struct* output = calloc(1, sizeof(ent_ext_table_struct));

	memcpy(output->name, parse_struct, (size_t) len);
	/* NOTE: Code address is still unknown */

	list_add_element(&(tables->entry_table), output);
	return 0;
}

int op_extern (OP_SIGNATURE) {
	int len = PARSER_GET_INT(parse_struct);
	ent_ext_table_struct* output = calloc(1, sizeof(ent_ext_table_struct));

	memcpy(output->name, parse_struct, (size_t) len);
	/* NOTE: Code address is still unknown */

	list_add_element(&(tables->extern_table), output);
	return 0;
}

/* OPs */
int op_mov (OP_SIGNATURE) {

	return 0;
}

int op_cmp (OP_SIGNATURE) {

	return 0;
}

int op_add (OP_SIGNATURE) {

	return 0;
}

int op_sub (OP_SIGNATURE) {

	return 0;
}

int op_not (OP_SIGNATURE) {

	return 0;
}

int op_clr (OP_SIGNATURE) {

	return 0;
}

int op_lea (OP_SIGNATURE) {

	return 0;
}

int op_inc (OP_SIGNATURE) {

	return 0;
}

int op_dec (OP_SIGNATURE) {

	return 0;
}

int op_jmp (OP_SIGNATURE) {

	return 0;
}

int op_bne (OP_SIGNATURE) {

	return 0;
}

int op_red (OP_SIGNATURE) {

	return 0;
}

int op_prn (OP_SIGNATURE) {

	return 0;
}

int op_jsr (OP_SIGNATURE) {

	return 0;
}

int op_rts (OP_SIGNATURE) {

	return 0;
}

int op_stop (OP_SIGNATURE) {

	return 0;
}