#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "errors.h"
#include "state.h"

/* Adds an element to a linked list pointer, and if it doesn't exist (ie. NULL), creates it and assigned to pointer */
void list_add_element (list** the_list, void* data) {
	if (data == NULL) {
		return;
	}

	if (*the_list == NULL) {
		*the_list = calloc(1, sizeof(list));

		/* Check if calloc failed */
		if (*the_list == NULL) {
			fprintf(stderr, ERROR_OUT_OF_MEMORY);
			exit(1);
		}

		/* Put new values in list node */
		(*the_list)->data = data;
	} else {
		list* ptr = *the_list;

		/* Skip to last element */
		while (ptr->next != NULL) {
			ptr = ptr->next;
		}

		ptr->next = calloc(1, sizeof(list));

		/* Check if calloc failed */
		if (ptr->next == NULL) {
			fprintf(stderr, ERROR_OUT_OF_MEMORY);
			exit(1);
		}

		/* Put new values in list node */
		ptr->next->data = data;
	}
}

void free_list (list* the_list, void (* free_data) (void*)) {
	list* next;

	while (the_list) {
		next = the_list->next;
		free_data(the_list->data);
		free(the_list);
		the_list = next;
	}
}

void free_refs (void* refs) {
	free(((ref_in_code*) refs)->name);
	free(refs);
}

void free_entry_with_line_num (void* entries) {
	free(((entry_with_line_num*) entries)->name);
	free(entries);
}

void free_data_labels (void* data_labels) {
	free(((data_label*) data_labels)->name);
	free(data_labels);
}

void free_code_labels (void* code_labels) {
	free(((code_label*) code_labels)->name);
	free(code_labels);
}
