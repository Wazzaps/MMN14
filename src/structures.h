#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_STRING_LENGTH 300

typedef char string[MAX_STRING_LENGTH + 1];

typedef struct entry_list {
	string name;
	unsigned int line_num;
	struct entry_list* next;
} entry_list;

typedef struct extern_list {
	string name;
	unsigned int line_num;
	struct extern_list* next;
} extern_list;

typedef struct label_list {
	string name;
	struct label_list* next;
} label_list;

#endif