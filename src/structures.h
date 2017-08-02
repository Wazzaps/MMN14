#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_STRING_LENGTH 300

typedef char string[MAX_STRING_LENGTH + 1];

typedef struct list {
	void* data;
	struct list* next;
} list;

typedef struct {
	char* name;
	unsigned int code_address;
} extern_ref;

typedef struct {
	string name;
	unsigned int data_address;
	unsigned int is_matrix:1;
	unsigned int matrix_size_x;
	unsigned int matrix_size_y;
} data_label;

typedef struct {
	string name;
	unsigned int code_address;
} code_label;

typedef int cpu_word;

struct assembler_state_tables {
	list* entry_table; // List of type 'char*'
	list* extern_table; // List of type 'char*'
	list* extern_refs_table; // List of type 'extern_ref'
	list* data_labels_table; // List of type 'data_label'
	list* code_labels_table; // List of type 'code_label'
	cpu_word* data; // Points to start of data table
	unsigned int data_current_size;
	cpu_word* code; // Points to start of code table
	unsigned int code_current_size;
};

/* Declarations */
void list_add_element (list** the_list, void* data);

#endif