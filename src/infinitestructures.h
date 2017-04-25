#ifndef INFINITESTRUCTURES_H 
#define INFINITESTRUCTURES_H 

char* string_expand_by (char* string, unsigned int length);
char* string_expand_to (char* string, unsigned int length);
char* string_concat (char* a, char* b);
char* string_copy (char* string);
char* string_append_char (char* string, char char_to_append);

void* array_expand_by (void* array, unsigned int length);

#endif