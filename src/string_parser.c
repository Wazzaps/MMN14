#include <stdio.h>
#include "string_parser.h"
#include "errors.h"
#include "general_parsing.h"

int myscanf(string format,
            parser_definition custom_types[],
            int custom_types_length,
            parser_definition searchables[],
            int searchables_length,
            string input, ...) {

    va_list args;
    int count;
    string current_format_name;
    va_start(args, input);

    char* inputptr = input;

    while(*format) {
        inputptr = advance_whitespace(inputptr);
        if (*format == '%' && (inputptr == input || *(format-1) == '\\')) {
            switch (*(++format)) {
                case 'a':

                    break;
                case '{':
                    count = 0;
                    while(*(++format) != '}' && *format != 0) {
                        current_format_name[count++] = *format;
                    }
                    current_format_name[count] = 0;
                    if (*format == 0) {
                        fprintf(stderr, ERROR_UNEXPECTED_FMT_END);
                        return -count;
                    }
                    /* Parse the format incoming string */
                    break;
                default:
                    fprintf(stderr, ERROR_NO_CURBRACE_AFTER_FORMAT);
                    return -count;
            }
        } else {
            if (*inputptr == *format) {
                inputptr++;
                if (*format == '\\') format++;
            } else {
                fprintf(stderr, ERROR_EXPECTED_CHARACTER, *format, inputptr - input);
                return -count;
            }
        }

        format++;
    }

    input = advance_whitespace(input);

    if (*input != 0) {
        fprintf(stdout, ERROR_UNPROCESSED_TEXT);
        return -count;
    }

    va_end(args);
    return count;
}