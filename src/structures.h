#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_STRING_LENGTH 300

typedef char string[MAX_STRING_LENGTH + 1];

typedef struct list {
	string name;
	unsigned int line_num;
	struct list* next;
} list;

typedef char* dataptr;

typedef char* codeptr;

/* Declarations */
void list_add_element (list** the_list, string name, unsigned int line_num);

#endif