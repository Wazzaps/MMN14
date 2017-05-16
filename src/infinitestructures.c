#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infinitestructures.h"

infstring* string_append_to_last (infstring* string, char char_to_append) {
	if (string->next_element != NULL) {
		printf("\nFATAL ERROR: string_append_to_last() CALLED ON NON LAST ELEMENT\n");
		exit(-1);
	}
	
	if (string->length == STRING_SINGLE_ELEMENT_LENGTH) {
		/* Create a new list element */
		infstring* new_element = calloc(1, sizeof(infstring));
		new_element->string[0] = char_to_append;
		new_element->length = 1;
		string->next_element = new_element;
		return new_element;
	} else {
		string->string[ string->length++ ] = char_to_append;
		return string;
	}
}

char* to_cstring (infstring* string) {
	unsigned int length;
	char* output;
	infstring* current = string;
	int i = 0; /* LL element iterator */
	int j = 0; /* Internal array iterator */

	if (!string) {
		printf("\nFATAL ERROR: INPUT STRING IS NULL\n");
		exit(-1);
	}

	length = string_length(string);
	output = calloc(length + 1, sizeof(char));

	while (current->next_element) {
		for (j = 0; j < STRING_SINGLE_ELEMENT_LENGTH; j++) {
			output[i * STRING_SINGLE_ELEMENT_LENGTH + j] = current->string[j];
		}
		i++;
		current = current->next_element;
	}

	for (j = 0; j < current->length; j++) {
		output[i * STRING_SINGLE_ELEMENT_LENGTH + j] = current->string[j];
	}

	output[length] = 0; /* Null terminator */

	return output;
}

infstring* from_cstring (char* string) {
	infstring* output = string_new();
	infstring* current = output;
	unsigned int i;
	unsigned int length = strlen(string);

	for (i = 0; i < length; i++) {
		current = string_append_to_last(current, string[i]);
	}

	return output;
}

void string_concat (infstring* a, infstring* b) {
	infstring* currentA = a;
	infstring* currentB = b;
	int i; /* A internal array iterator */
	int j; /* B internal array iterator */

	/* Bring our `a` element to the tail of the list */
	while (currentA->next_element != NULL) {
		currentA = currentA->next_element;
	}

	/* Advance iterator to `a`'s current position */
	i = currentA->length;

	while (currentB != NULL) { /* Iterates over `b`'s elements */
		for (j = 0; j < currentB->length; j++) { /* Iterates over `b`'s array elements */
			if (i == STRING_SINGLE_ELEMENT_LENGTH) {
				/* Create a new list element */
				infstring* new_element = calloc(1, sizeof(infstring));
				currentA->next_element = new_element;
				currentA = new_element;
				currentA->string[0] = currentB->string[j];
				currentA->length = 1;
				i = 1;
			} else {
				currentA->string[ currentA->length++ ] = currentB->string[j];
				i++;
			}
		}
		currentB = currentB->next_element;
	}
}

char string_get_char (infstring* string, unsigned int position) {
	unsigned int i = 0;
	int j;
	
	while (string != NULL) {
		if (position - i < STRING_SINGLE_ELEMENT_LENGTH) {
			for (j = 0; j < STRING_SINGLE_ELEMENT_LENGTH; j++) {
				if (i + j == position)
					return string->string[j];
			}
		} else {
			string = string->next_element;
			i += STRING_SINGLE_ELEMENT_LENGTH;
		}
	}
	return 0;
}

char string_get_next_char (infstring** string, int* currentpos) {
	if ((*currentpos) == STRING_SINGLE_ELEMENT_LENGTH) {
		(*string) = (*string)->next_element;
		(*currentpos) = 0;
	}
	return (*string)->string[(*currentpos)++];
}

unsigned int string_length (infstring* string) {
	infstring* current = string;
	unsigned int length = 0;

	while (current != NULL) {
		length += current->length;
		current = current->next_element;
	}

	return length;
}



/*char* string_concat (char* a, char* b) {
	unsigned int a_length = strlen(a);
	unsigned int b_length = strlen(b);
	char* output = malloc(a_length + b_length + 1);

	memcpy(output, a, a_length);
	memcpy(output + a_length, b, b_length + 1);

	return output;
}

char* string_copy (char* string) {
	unsigned int length = strlen(string);
	char* output = malloc(length + 1);
	memcpy(output, string, length);
	return output;
}*/

void string_append_char (infstring* string, char char_to_append) {
	string_append_to_last (string_get_last_elem(string), char_to_append);
}

void* array_expand_to (void* array, unsigned int length, unsigned int size) {
	return realloc(array, length * size);
}

void string_free (infstring* string) {
	if (string->next_element != NULL) {
		string_free(string->next_element);
	}	
	free(string);
}

infstring* string_new () {
	return calloc(1, sizeof(infstring));
}

infstring* string_get_last_elem (infstring* string) {
	while (string->next_element) {
		string = string->next_element;
	}
	return string;
}