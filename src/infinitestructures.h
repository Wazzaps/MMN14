#ifndef INFINITESTRUCTURES_H 
#define INFINITESTRUCTURES_H 

#define STRING_SINGLE_ELEMENT_LENGTH 8

typedef struct infstring {
	unsigned int length;
	char string[STRING_SINGLE_ELEMENT_LENGTH];
	struct infstring* next_element;
} infstring;

infstring* string_append_to_last (infstring* string, char char_to_append);
char* to_cstring (infstring* string);
infstring* from_cstring (char* string);
void string_concat (infstring* a, infstring* b);
infstring* string_copy (infstring* string);
void string_append_char (infstring* string, char char_to_append);
char string_get_char (infstring* string, unsigned int position);
char string_get_next_char (infstring** string, int* currentpos);
unsigned int string_length (infstring* string);
void string_free (infstring* string);
infstring* string_new ();
infstring* string_get_last_elem (infstring* string);

void* array_expand_to (void* array, unsigned int length, unsigned int size);

#endif