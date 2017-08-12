#ifndef MMN14_STATE_H
#define MMN14_STATE_H

#include <stdio.h>
#include "list.h"
#include "cpu_word.h"

typedef struct {
	char* name;
	unsigned code_address;
} ref_in_code;

typedef struct {
	char* name;
	unsigned address;
	unsigned is_matrix:1;
} data_label;

typedef struct {
	char* name;
	unsigned address;
} code_label;


typedef struct  {
	/* Assembler tables */
	list* entry_table; // List of type 'char*'
	list* extern_table; // List of type 'char*'
	list* extern_refs_table; // List of type 'ref_in_code'
	list* data_labels_table; // List of type 'data_label'
	list* code_labels_table; // List of type 'code_label'
	list* code_label_refs_table; // List of type 'ref_in_code'
	cpu_word* data_table; // Points to start of data table
	unsigned int data_counter;
	cpu_word* code_table; // Points to start of code table
	unsigned int code_counter;

	/* Current file info */
	char* current_file_name;
	FILE* current_file_ptr;
	int current_line_num;
	int failed;
} state_t;

#endif //MMN14_STATE_H
