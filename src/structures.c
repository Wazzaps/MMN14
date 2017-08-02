#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "errors.h"

// Adds an element to a linked list pointer, and if it doesn't exist (ie. NULL), creates it and assigned to pointer
void list_add_element (list** the_list, void* data) {
	if (data == NULL) {
		return;
	}

	if (*the_list == NULL) {
		*the_list = calloc(1, sizeof(list));

		// Check if calloc failed
		if (*the_list == NULL) {
			fprintf(stderr, ERROR_OUT_OF_MEMORY);
			exit(1);
		}

		// Put new values in list node
		(*the_list)->data = data;
	} else {
		list* ptr = *the_list;

		// Skip to last element
		while (ptr->next != NULL) {
			ptr = ptr->next;
		}

		ptr->next = calloc(1, sizeof(list));

		// Check if calloc failed
		if (ptr->next == NULL) {
			fprintf(stderr, ERROR_OUT_OF_MEMORY);
			exit(1);
		}

		// Put new values in list node
		ptr->next->data = data;
	}
}