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

#endif //MMN14_CONSTANT_DATA_H
