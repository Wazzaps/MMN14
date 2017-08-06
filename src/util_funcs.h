#ifndef MMN14_UTIL_FUNCS_H
#define MMN14_UTIL_FUNCS_H

#include "state.h"

char* file_add_extension (char* original, char extension[3]);

int get_line (char* buffer, int length, FILE* stream, int line_num);

char* split_label_and_code (char* line);

void remove_comment (char* line);

char* advance_whitespace (char* str);

char* advance_nonwhitespace (char* str);

char* block_whitespace (char* str);

void clean_and_split_line (char* line, char** _label_name, char** _name, char** _code_contents, state_t*, int show_errors);

int is_valid_label (char* name);

#endif //MMN14_NEW_UTIL_FUNCS_H
