#ifndef GENERAL_PARSING_H
#define GENERAL_PARSING_H

#define MAX_LABEL_NAME_LENGTH 30

char* split_label_and_code(char *line);
void remove_comment(char *line);
char* advance_whitespace(char* str);
char* block_whitespace(char* str);
void clean_and_preprocess_line(char *line, char **_label_name, char **_code_contents, int line_num);

#endif //GENERAL_PARSING_H
