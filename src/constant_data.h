#ifndef MMN14_CONSTANT_DATA_H
#define MMN14_CONSTANT_DATA_H

#include "state.h"

typedef enum {
	NONE = 0,
	CONST = 1,
	LABEL = 2,
	MATRX = 4,
	REGIS = 8
} operand_e;

typedef enum {
	ABSOLUTE = 0,
	EXTERNAL = 1,
	RELOCATABLE = 2,
	CODE_LABEL = 3
} linking_type_e;

typedef enum {
	SRC = 0,
	DST = 1
} operand_type_e;

typedef struct {
	char* name;
	unsigned number_of_operands;
	operand_e src_t;
	operand_e dst_t;
} op_t;

typedef struct {
	char* name;
	int (* func) (state_t*, char*, char*);
} direc_t;


#define OPS_LENGTH 16
extern op_t OPS[];

#define DIRECTIVES_LENGTH 5
extern direc_t DIRECTIVES[];

#define LINE_LENGTH 80

#define MINIMUM_REG 0
#define MAXIMUM_REG 7

#define ASM_EXT "as"
#define OBJ_EXT "ob"
#define EXT_EXT "ext"
#define ENT_EXT "ent"

#define MAX_VALUE_UNSIGNED 1023
#define MAX_VALUE_SIGNED 511
#define MIN_VALUE_SIGNED -512

#define MEM_STARTS_AT 100

#endif //MMN14_CONSTANT_DATA_H
