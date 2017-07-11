#ifndef DIRECTIVE_PARSER_H
#define DIRECTIVE_PARSER_H

void parse_directives (FILE* fp, string file_name, list** entry_list, list** extern_list,
                       list** label_list, dataptr* data, codeptr* code);

#endif //DIRECTIVE_PARSER_H
