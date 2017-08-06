#include "state.h"

#ifndef MMN14_PARSING_H
#define MMN14_PARSING_H

int maybe_char (char, char** ptr);

#define MAYBE_CHAR(c) maybe_char((c), &ptr)

int expect_char (char, char** ptr, state_t*);

#define EXPECT_CHAR(c) expect_char((c), &ptr, state)

int maybe_number (long*, char** ptr);

#define MAYBE_NUMBER(n) maybe_number(&(n), &ptr)

int expect_number (long*, char** ptr, state_t*);

#define EXPECT_NUMBER(n) expect_number(&(n), &ptr, state)

int expect_whitespace_or_eol (char** ptr, state_t*);

#define EXPECT_SPACE_OR_EOL() expect_whitespace_or_eol(&ptr, state)

#endif //MMN14_PARSING_H
