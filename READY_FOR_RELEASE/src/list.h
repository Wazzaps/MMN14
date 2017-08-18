#ifndef MMN14_LIST_H
#define MMN14_LIST_H


typedef struct list {
	void* data;
	struct list* next;
} list;


void list_add_element (list** the_list, void* data);

void free_list (list* the_list, void (* free_data) (void*));

void free_refs (void* refs);

void free_entry_with_line_num (void* entries);

void free_data_labels (void* data_labels);

void free_code_labels (void* code_labels);

#endif /* MMN14_NEW_LIST_H */
