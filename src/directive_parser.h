#ifndef DIRECTIVE_PARSER_H
#define DIRECTIVE_PARSER_H

void parse_directives(FILE *fp, string file_name, entry_list *entry_table,
                      extern_list *extern_table, label_list *label_table);

#endif //DIRECTIVE_PARSER_H
