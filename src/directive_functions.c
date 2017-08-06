#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "directive_functions.h"
#include "string_parser.h"

/* Directive processor functions */

// Format: comma_seperated_array_of_ints
// Parser struct format:
// - Number of elements:int
// - Element 1:int
// - Element 2:int
// - ...
// - Element n:int
int decl_data (DECL_SIGNATURE) {
	int data_size = PARSER_GET_INT(parse_struct);
    void *new_data = NULL;

    if (label_name != NULL) {
        data_label *new = malloc(sizeof(data_label));
        if (!new)
            return 0;
        strcpy(new->name, label_name);
        new->data_address = tables->code_current_size;
        list_add_element(&(tables->data_labels_table), new);
    }

    new_data = realloc(tables->data, sizeof(cpu_word) * (tables->data_current_size + data_size));
    if (!new_data) {
        return 0;
    }

    tables->data = new_data;

    // FIXME: REMOVE ME
	int i;
	printf("GOT DATA: ");
	for (i = 0; i < data_size; i++) {
        int current = PARSER_GET_INT(parse_struct);
        printf("%d, ", current);

        tables->data[tables->data_current_size + i] = current; // TODO: confirm the base / format
	}
	putchar('\n');
	// FIXME: END REMOVE ME

	// TODO: Save label with current data size in label table
	// TODO: Save data in data table
	return data_size;
}

// Format: "array_of_printable_characters_except_parentheses"
// Parser struct format:
// - Length of string:int
// - Char 1:char
// - ...
// - Char n:char
int decl_string (DECL_SIGNATURE) {
	int data_size = PARSER_GET_INT(parse_struct) * sizeof(int);

    void *new_data = NULL;

    if (label_name != NULL) {
        data_label *new = malloc(sizeof(data_label));
        if (!new)
            return 0;
        strcpy(new->name, label_name);
        new->data_address = tables->code_current_size;
        list_add_element(&(tables->data_labels_table), new);
    }

    new_data = realloc(tables->data, sizeof(cpu_word) * (tables->data_current_size + data_size));
    if (!new_data) {
        return 0;
    }

    tables->data = new_data;

    // FIXME: REMOVE ME
	int i;
	printf("GOT STRING: ");
	for (i = 0; i < data_size / 4; i++) {
		putchar(PARSER_GET_CHAR(parse_struct));
	}
	putchar('\n');
	// FIXME: END REMOVE ME

	// TODO: Save label with current data size in label table
	// TODO: Save data in data table
	return data_size;
}

// Format: [sizex][sizey] array_of_comma_seperated_init_values
// Parser struct format:
// - Size X:int
// - Size Y:int
// - Length of data initializers array:int
// - Number 1:int
// - ...
// - Number n:int
int decl_mat (DECL_SIGNATURE) {
	int init_length;
	int data_size = 0;
	int mat_size_x = PARSER_GET_INT(parse_struct);
	int mat_size_y = PARSER_GET_INT(parse_struct);
    void *new_data = NULL;

    init_length = mat_size_x * mat_size_y;

    if (label_name != NULL) {
        data_label *new = malloc(sizeof(data_label));
        if (!new)
            return 0;
        strcpy(new->name, label_name);
        new->data_address = tables->code_current_size;
        list_add_element(&(tables->data_labels_table), new);
    }

    new_data = realloc(tables->data, sizeof(cpu_word) * (tables->data_current_size + init_length));
    if (!new_data) {
        return 0;
    }

    tables->data = new_data;

	// FIXME: REMOVE ME
	int i;

	printf("GOT MATRIX NAMED '%s' OF SIZE %dx%d WITH VALUES: ", label_name, mat_size_x, mat_size_y);

	init_length = PARSER_GET_INT(parse_struct);

	for (i = 0; i < init_length; i++) {
		printf("%d, ", PARSER_GET_INT(parse_struct));
	}

	putchar('\n');
	// FIXME: END REMOVE ME

	// TODO: Save label with current data size in label table
	// TODO: Save data in data table
	return data_size;
}

// Format: name_of_entry
// Parser struct format:
// - Length of string:int
// - Char 1:char
// - ...
// - Char n:char
int decl_entry (DECL_SIGNATURE) {
	int len = PARSER_GET_INT(parse_struct);
	char* output = calloc(1, (size_t) len + 1);

	memcpy(output, parse_struct, (size_t) len);
	output[len] = '\0';

	printf("ADDED ENTRY: %s\n", output);

	list_add_element(&(tables->entry_table), output);
	return 0;
}

// Format: name_of_extern
// Parser struct format:
// - Length of string:int
// - Char 1:char
// - ...
// - Char n:char
int decl_extern (DECL_SIGNATURE) {
	int len = PARSER_GET_INT(parse_struct);
	char* output = calloc(1, (size_t) len + 1);

	memcpy(output, parse_struct, (size_t) len);
	output[len] = '\0';

	printf("ADDED EXTERN: %s\n", output);

	list_add_element(&(tables->extern_table), output);
	return 0;
}