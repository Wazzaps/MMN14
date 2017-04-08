#ifndef LEXER_ENUMS_H
#define LEXER_ENUMS_H

enum lexer_modes {
    CODE,
    IN_COMMENT,
    IN_STRING,
    IN_CHAR
};

enum lexer_token {
    /* Simple chars, escapable */
    ESCAPE = 0,
    NEWLINE,
    QUOTATION_MARK,
    APOSTROPHE,

    /* Simple chars, unescapable */
    OPEN_BRACKET = 1000,
    CLOSE_BRACKET,
    OPEN_PARENTHESIS,
    CLOSE_PARENTHESIS,
    OPEN_CURLYBRACE,
    CLOSE_CURLYBRACE,
    OPEN_ANGLEBRACKET,
    CLOSE_ANGLEBRACKET,
    EQUAL_SIGN,
    PLUS_SIGN,
    MINUS_SIGN,
    MULTIPLY_SIGN,
    DIVIDE_SIGN,
    MODULO_SIGN,
    BITWISE_NOT,
    BITWISE_AND,
    BITWISE_OR,
    BITWISE_XOR,
    LOGICAL_NOT,
    SEMICOLON,
    COLON,
    COMMA,
    DOT,
    QUESTION_MARK,
    HASH,
    WIDE_MARKER,
    
    
    /* Simple strings, unescapable */
    OPEN_COMMENT = 2000,
    CLOSE_COMMENT,
    INCREMENT,
    DECREMENT,
    POINTER_ARROW,
    LOGICAL_AND,
    LOGICAL_OR,
    LOGICAL_EQUALS,
    LOGICAL_DOESNT_EQUAL,
    LOGICAL_MORE_OR_EQ,
    LOGICAL_LESS_OR_EQ,
    CURRENT_LINE_MACRO,
    CURRENT_FILE_MACRO,

    /* Special case */
    DECIMAL_NUMBER = 3000,
    HEX_NUMBER,
    OCTAL_NUMBER,
    WHITESPACE,
    WORD
};

#endif