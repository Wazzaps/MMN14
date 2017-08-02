#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "string_parser.h"
#include "general_parsing.h"
#include "errors.h"

#define STRUCT_SIZE_INCREMENT 10

int
_general_parse (string format, char** input, char* orig_input, void** output_struct, int* struct_pos, int* struct_size,
                int custom_types_length, parser_definition custom_types[], int line_num, int show_errors);

int
_multi_parse (string format, char** input, char* orig_input, void** output_struct, int* struct_pos, int* struct_size,
              int custom_types_length, parser_definition custom_types[], int line_num, int show_errors);

int
_single_parse (string format, char** input, char* orig_input, void** output_struct, int* struct_pos, int* struct_size,
               int custom_types_length, parser_definition custom_types[], int line_num, int show_errors);

char* _get_friendly_name (string inner_format, int custom_types_length, parser_definition custom_types[]);

void _replace_vertical_bar_with_null (string);

void _print_friendly_types (FILE*, string inner_format_name, int custom_types_length, parser_definition custom_types[]);

void _adjust_struct_size (void** output_struct, int* struct_size, int wanted_size);

void* mysscanf (string format, int custom_types_length, parser_definition custom_types[], char* input,
                int fail_on_excessive_text, int line_num) {
	void* output_struct = malloc(1);
	int struct_size = 0;
	int struct_pos = 0;
	int parsing_result;
	char* orig_input = input;

	parsing_result = _general_parse(format, &input, input, &output_struct, &struct_pos, &struct_size,
	                                custom_types_length,
	                                custom_types, line_num, 1);
	if (parsing_result == 0) {
		free(output_struct);
		return 0;
	}
	if (*input != 0 && fail_on_excessive_text) {
		fprintf(stderr, ERROR_UNPROCESSED_TEXT, line_num, input - orig_input);
		free(output_struct);
		return 0;
	}
	return output_struct;
}

/* Parses complete format strings (with %{stuff} and escapes) */
int
_general_parse (string format, char** input, char* orig_input, void** output_struct, int* struct_pos, int* struct_size,
                int custom_types_length, parser_definition custom_types[], int line_num, int show_errors) {
	// Skip beginning whitespace
	*input = advance_whitespace(*input);
	while (*format != 0) {
		if (*format == ' ') {
			*input = advance_whitespace(*input);
		}
		if (*format == '\\') {
			format++;
			if (**input == *format) {
				format++;
				continue;
			} else if (show_errors) {
				fprintf(stderr, ERROR_EXPECTED_CHARACTER, *format, **input, **input, line_num);
				return 0;
			}
		}
		if (*format == '%') {
			int is_array = 0;
			int is_comma_delimited = 0;
			format++;

			if (*format == 'a') {
				is_array = 1;
				format++;
			}

			if (*format == 'c') {
				is_array = 1;
				is_comma_delimited = 1;
				format++;
			}

			if (*format == '{') {
				char* inner_format_name = NULL;
				char* end_of_format_name;
				int type_option;
				int is_multi_option = 0;
				int num_of_elements = 0;
				int array_length_pos = *struct_pos;
				int type_option_pos = 0;

				// Leave space for the array length
				if (is_array) {
					_adjust_struct_size(output_struct, struct_size, *struct_pos += sizeof(int));
				}

				format++;
				end_of_format_name = strchr(format, '}');
				inner_format_name = calloc(end_of_format_name - format + 1, sizeof(char));

				// Loop over array elements
				do {
					// Create a fresh copy of the format
					strncpy(inner_format_name, format, end_of_format_name - format);

					// Leave space for the option index if needed
					if (strchr(inner_format_name, '|')) {
						is_multi_option = 1;
						type_option_pos = *struct_pos;
						_adjust_struct_size(output_struct, struct_size, *struct_pos += sizeof(int));
					}

					// Parse
					type_option = _multi_parse(inner_format_name, input, orig_input, output_struct, struct_pos,
					                           struct_size,
					                           custom_types_length, custom_types, line_num,
					                           show_errors && !is_multi_option);

					// If successful, store the type option index, or else free space
					if (type_option) {
						if (is_multi_option)
							*((int*) (*output_struct + type_option_pos)) = type_option;
						if (is_array) {
							num_of_elements++;
							// Skip whitespace
							if (is_comma_delimited) {
								*input = advance_whitespace(*input);
								if (**input == ',') {
									(*input)++;
									*input = advance_whitespace(*input);
								} else {
									break;
								}
							}
						}
					} else {

						if (!is_array || is_comma_delimited) {
							if (is_multi_option) {
								// TODO: ERROR: Did not match any type
								if (show_errors) {
									//puts("ERROR: Did not match any type");
									fprintf(stderr, ERROR_UNMATCHED_TYPES, line_num);
									// Make sure vertical bars are nulled, for the print function below
									_replace_vertical_bar_with_null(inner_format_name);
									_print_friendly_types(stderr, inner_format_name, custom_types_length, custom_types);
								}

								_adjust_struct_size(output_struct, struct_size, *struct_pos -= sizeof(int));
							} else if (show_errors) {
								fprintf(stderr, ERROR_UNMATCHED_TYPE,
								        _get_friendly_name(inner_format_name, custom_types_length, custom_types),
								        line_num, *input - orig_input);
							}

							// Free format name
							free(inner_format_name);
							return 0;
						}

					}
				} while (is_array && type_option);

				// Free format name
				free(inner_format_name);

				// Skip to after '}'
				format = end_of_format_name + 1;

				// If an array and have any elements, store the length of the array, or else free space
				if (is_array) {
					if (num_of_elements) {
						*((int*) (*output_struct + array_length_pos)) = num_of_elements;
					} else {
						_adjust_struct_size(output_struct, struct_size, *struct_pos -= sizeof(int));
						return 0;
					}
				}
			} else {
				if (show_errors) {
					// TODO: ERROR: Unexpected '%'
					puts("ERROR: Unexpected '%'");
				}
				return 0;
			}

		} else {
			if (**input == *format) {
				format++;
				(*input)++;
			} else {
				if (show_errors) {
					if (**input == '\0')
						fprintf(stderr, ERROR_EXPECTED_CHARACTER_EOL, *format, line_num);
					else
						fprintf(stderr, ERROR_EXPECTED_CHARACTER, *format, **input, **input, line_num);
				}
				return 0;
			}
		}
	}
	return 1;
}

/* Parses type1|type2|type3 etc. Kinda like strtok.
 * Returns which type matched, or 0 if none. */
int
_multi_parse (string format, char** input, char* orig_input, void** output_struct, int* struct_pos, int* struct_size,
              int custom_types_length, parser_definition custom_types[], int line_num, int show_errors) {
	int counter = 1;
	char* next;
	char* input_before = *input;
	if (**input == '\0')
		return 0;
	while ((next = strchr(format, '|'))) {
		input_before = *input;
		*next = '\0';
		if (_single_parse(format, input, orig_input, output_struct, struct_pos, struct_size, custom_types_length,
		                  custom_types, line_num, 0)) {
			return counter;
		} else {
			*input = input_before;
		}
		format = next + 1;
		counter++;
	}
	input_before = *input;
	if (_single_parse(format, input, orig_input, output_struct, struct_pos, struct_size, custom_types_length,
	                  custom_types, line_num, show_errors && counter == 0)) {
		return counter;
	} else {
		*input = input_before;
	}
	return 0;
}

/* Parses a single type, returns 1 on success or 0 on fail */
int
_single_parse (string format, char** input, char* orig_input, void** output_struct, int* struct_pos, int* struct_size,
               int custom_types_length, parser_definition custom_types[], int line_num, int show_errors) {
	// Check if it is a base type (int or word)
	if (!strcmp(format, "int")) {
		long parsed_result;
		char* end_ptr;
		parsed_result = strtol(*input, &end_ptr, 10);
		if (end_ptr == *input) {
			return 0;
		} else {
			_adjust_struct_size(output_struct, struct_size, *struct_pos + sizeof(int));
			*((int*) (*output_struct + *struct_pos)) = (int) parsed_result;
			*struct_pos += sizeof(int);
			*input = advance_whitespace(end_ptr);
			return 1;
		}
	} else if (!strcmp(format, "char")) {
		if (**input == '\0') {
			return 0;
		} else {
			_adjust_struct_size(output_struct, struct_size, *struct_pos + sizeof(char));
			*((char*) (*output_struct + *struct_pos)) = **input;
			*struct_pos += sizeof(char);
			(*input)++;
			return 1;
		}
	} else if (!strcmp(format, "alphanumchar")) {
		if (!isalnum(**input)) {
			return 0;
		} else {
			_adjust_struct_size(output_struct, struct_size, *struct_pos + sizeof(char));
			*((char*) (*output_struct + *struct_pos)) = **input;
			*struct_pos += sizeof(char);
			(*input)++;
			return 1;
		}
	} else if (!strcmp(format, "charinstring")) {
		if (!isprint(**input) || **input == '"') {
			return 0;
		} else {
			_adjust_struct_size(output_struct, struct_size, *struct_pos + sizeof(char));
			*((char*) (*output_struct + *struct_pos)) = **input;
			*struct_pos += sizeof(char);
			(*input)++;
			return 1;
		}
	} else if (!strcmp(format, "word")) {
		int _parse_result = _general_parse("%a{alphanumchar}", input, orig_input, output_struct, struct_pos,
		                                   struct_size, custom_types_length,
		                                   custom_types, line_num, show_errors);
		return _parse_result;
	} else if (!strcmp(format, "quotedstring")) {
		return _general_parse("\"%a{charinstring}\"", input, orig_input, output_struct, struct_pos, struct_size,
		                      custom_types_length,
		                      custom_types, line_num, show_errors);
	} else if (!strcmp(format, "disabled")) {
		return 0;
	} else {
		// Check for custom types
		int i;
		for (i = 0; i < custom_types_length; i++) {
			if (!strcmp(format, custom_types[i].name)) {
				//printf("%s: %s\n", custom_types[i].format, custom_types[i].friendly_name);
				return _general_parse(custom_types[i].format, input, orig_input, output_struct, struct_pos, struct_size,
				                      custom_types_length, custom_types, line_num, show_errors);
			}
		}

		// Not found
		return 0;
	}
}

// Looks up the friendly name of a format
char* _get_friendly_name (string inner_format, int custom_types_length, parser_definition custom_types[]) {
	int i;
	for (i = 0; i < custom_types_length; i++) {
		if (!strcmp(inner_format, custom_types[i].name)) {
			return custom_types[i].friendly_name;
		}
	}
	return inner_format;
}

// Replaces all '|'s with '\0's
void _replace_vertical_bar_with_null (string str) {
	while (*str != '\0') {
		if (*str == '|') {
			*str = '\0';
		}
		str++;
	}
}

// Print all friendly versions of a string, containing format names seperated by \0
void
_print_friendly_types (FILE* fp, string inner_format_name, int custom_types_length, parser_definition custom_types[]) {
	char* original_ptr = inner_format_name;
	while (inner_format_name - original_ptr < sizeof(string) &&
	       (*inner_format_name != '\0')) {
		if (strcmp(inner_format_name, "disabled"))
			fprintf(fp, "- %s\n", _get_friendly_name(inner_format_name, custom_types_length, custom_types));
		while (*inner_format_name != '\0') {
			inner_format_name++;
		}
		inner_format_name++;
	}


}

// Increases a struct's size with Realloc
void _adjust_struct_size (void** output_struct, int* struct_size, int wanted_size) {
	int converted_size = ((wanted_size + (STRUCT_SIZE_INCREMENT - 1)) / STRUCT_SIZE_INCREMENT) * STRUCT_SIZE_INCREMENT;
	if (*struct_size < converted_size) {
		*struct_size = converted_size;
		*output_struct = realloc(*output_struct, (size_t) converted_size);
		if (*output_struct == NULL) {
			fprintf(stderr, ERROR_OUT_OF_MEMORY);
			exit(1);
		}
	}
}