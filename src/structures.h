#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_STRING_LENGTH 300

typedef char string[MAX_STRING_LENGTH + 1];

typedef struct list {
	void* data;
	struct list* next;
} list;

typedef struct {
	string name;
	unsigned int code_address;
} ent_ext_table_struct;

typedef struct {
	string name;
	unsigned int data_address;
	unsigned int is_matrix:1;
	unsigned int matrix_size_x;
	unsigned int matrix_size_y;
} data_labels_table_struct;

typedef struct {
	string name;
	unsigned int code_address;
} code_labels_table_struct;

typedef char* dataptr;

typedef char* codeptr;

struct assembler_state_tables {
	list* entry_table;
	list* extern_table;
	list* data_labels_table;
	list* code_labels_table;
	dataptr data;
	codeptr code;
};

/* Declarations */
void list_add_element (list** the_list, void* data);

#endif