#ifndef MMN14_LIST_H
#define MMN14_LIST_H

typedef struct list {
	void* data;
	struct list* next;
} list;

void list_add_element (list** the_list, void* data);

#endif //MMN14_NEW_LIST_H
