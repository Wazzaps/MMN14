#ifndef WHITESPACE_H 
#define WHITESPACE_H 

#include "infinitestructures.h"

infstring* whitespace_process (infstring* code);
infstring* _whitespace_firstpass (infstring* code);
infstring* _whitespace_secondpass (infstring* code);
infstring* _whitespace_thirdpass (infstring* code);

#endif