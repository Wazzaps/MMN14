#include "state.h"

#ifndef MMN14_PARSE_DIRECTIVES_H
#define MMN14_PARSE_DIRECTIVES_H

#define ASCII_ZERO 48

#define ISDIRECTIVE(d) ((d)[0] == '.')

void parse_directives_and_labels(state_t*);

void add_label(state_t *state, char *label);

int direc_data (state_t*, char*, char*);

int direc_string (state_t*, char*, char*);

int direc_mat (state_t*, char*, char*);

int direc_entry (state_t*, char*, char*);

int direc_extern (state_t*, char*, char*);

#endif //MMN14_PARSE_DIRECTIVES_H
