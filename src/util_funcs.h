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

char* str_dup (char* str);

void clean_and_split_line (char* line, char** _label_name, char** _name, char** _code_contents, state_t*, int show_errors);

int check_if_label_exists (state_t* state, char* label);

int is_valid_label (char* name, state_t* state);

data_label* find_data_label (state_t* state, char* label);

code_label* find_code_label (state_t* state, char* label);

void add_data_label (state_t* state, char* label);

void add_code_label (state_t* state, char* label);

int is_register_valid (long reg_num);

int is_extern_label (state_t* state, char* label);

void add_ref_in_code (list** table, char* label, unsigned address);

#endif /* MMN14_NEW_UTIL_FUNCS_H */
