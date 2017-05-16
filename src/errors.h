#ifndef ERRORS_H 
#define ERRORS_H 

typedef enum {
	NO_ERROR = 0,
	MISSING_INPUT_FILES = 1,
	MISSING_FLAG_ARGUMENT = 2,
	UNKNOWN_FLAG = 3,
	ERROR_FILEWRITE = 4,
	ERROR_FILEREAD = 5
} errorcode;

#endif