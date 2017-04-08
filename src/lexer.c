/* This file is responsible for taking the c file string
   and making it a list of tokens, with linear structure */
#include "lexer.h"

char isAlphabet(char input) {
    return (input >= 65 && input <= 90) || (input >= 97 && input <= 122);
}

char isDigit(char input) {
    return input >= 48 && input <= 57;
}

char getDigit(char input) {
    return input - 48;
}