#ifndef ERRORS_H 
#define ERRORS_H 

typedef enum {
	NO_ERROR = 0,
	MISSING_INPUT_FILES,
	MISSING_FLAG_ARGUMENT,
	UNKNOWN_FLAG
} errorcode;

#endif