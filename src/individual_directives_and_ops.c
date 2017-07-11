//
// Created by david on 7/4/17.
//

#include <stdio.h>
#include <string.h>
#include "individual_directives_and_ops.h"
#include "string_parser.h"

/* Directives */
void op_data (OP_SIGNATURE) {

}

void op_string (OP_SIGNATURE) {

}

void op_mat (OP_SIGNATURE) {

}

void op_entry (OP_SIGNATURE) {
	int len = PARSER_GET_INT(parse_struct);
	string name = "";
	memcpy(name, parse_struct, (size_t) len);

	list_add_element(entry_list, name, line_num);
}

void op_extern (OP_SIGNATURE) {

}

/* OPs */
void op_mov (OP_SIGNATURE) {

}

void op_cmp (OP_SIGNATURE) {

}

void op_add (OP_SIGNATURE) {

}

void op_sub (OP_SIGNATURE) {

}

void op_not (OP_SIGNATURE) {

}

void op_clr (OP_SIGNATURE) {

}

void op_lea (OP_SIGNATURE) {

}

void op_inc (OP_SIGNATURE) {

}

void op_dec (OP_SIGNATURE) {

}

void op_jmp (OP_SIGNATURE) {

}

void op_bne (OP_SIGNATURE) {

}

void op_red (OP_SIGNATURE) {

}

void op_prn (OP_SIGNATURE) {

}

void op_jsr (OP_SIGNATURE) {

}

void op_rts (OP_SIGNATURE) {

}

void op_stop (OP_SIGNATURE) {

}