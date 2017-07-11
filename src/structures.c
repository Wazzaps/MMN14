#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "errors.h"

void list_add_element (list** the_list, string name, unsigned int line_num) {
	if (*the_list == NULL) {
		*the_list = calloc(1, sizeof(list));

		// Check if calloc failed
		if (*the_list == NULL) {
			fprintf(stderr, ERROR_OUT_OF_MEMORY);
			exit(1);
		}

		// Put new values in list node
		strncpy((*the_list)->name, name, MAX_STRING_LENGTH + 1);
		(*the_list)->line_num = line_num;
	} else {
		// Skip to last element
		while ((*the_list)->next != NULL) {
			*the_list = (*the_list)->next;
		}

		(*the_list)->next = calloc(1, sizeof(list));

		// Check if calloc failed
		if ((*the_list)->next == NULL) {
			fprintf(stderr, ERROR_OUT_OF_MEMORY);
			exit(1);
		}

		// Put new values in list node
		strncpy((*the_list)->next->name, name, MAX_STRING_LENGTH + 1);
		(*the_list)->next->line_num = line_num;
	}
}