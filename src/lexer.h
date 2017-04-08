#ifndef LEXER_H
#define LEXER_H
#include "lexer_enums.h"

void lex(char* input); /* TODO: Make this return a linked list */

char isAlphabet(char input);
char isDigit(char input);
char getDigit(char input);

char lexer_token_chars_escapable[] = {
    '\\',
    '\n',
    '"',
    '\''
};

char lexer_token_chars_unescapable[] = {
    '[',
    ']',
    '(',
    ')',
    '{',
    '}',
    '<',
    '>',
    '=',
    '+',
    '-',
    '*',
    '/',
    '%',
    '~',
    '&',
    '|',
    '^',
    '!',
    ';',
    ':',
    ',',
    '.',
    '?',
    '#',
    'L'
};

char* lexer_token_strings[] = {
    "/*",
    "*/",
    "++",
    "--",
    "->",
    "&&",
    "||",
    "==",
    "!=",
    ">=",
    "<=",
    "__LINE__",
    "__FILE__"
};


typedef struct TOKEN_STRUCT {
    enum lexer_token type;
    int line;
    int col;
} TOKEN;

#endif