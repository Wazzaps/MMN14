#ifndef ERRORS_H 
#define ERRORS_H

/* Files */
#define ERROR_NO_INPUT_FILES "ERROR: Missing input files\n"
#define ERROR_CANNOT_READ "ERROR: Cannot read the file: %s\n"
#define ERROR_CANNOT_WRITE "ERROR: Cannot write the file: %s\n"
#define ERROR_LINE_TOO_LONG "WARN: Line number %d in file `%s` longer than the max allowed (%d). Truncated\n"

/* Labels */
#define ERROR_EMPTY_LABEL "WARN: Empty label on line %d\n"
#define ERROR_USELESS_LABEL "WARN: Useless label, no directive or operation on line %d\n"
#define ERROR_LABEL_TOO_LONG "WARN: Labels must have a maximum of %d characters, Violation on line %d\n"
#define ERROR_LABEL_NOT_ON_START_OF_LINE "WARN: Labels must be at the start of the line, no whitespace, Violation on line %d\n"
#define ERROR_WHITESPACE_AFTER_LABEL "WARN: Whitespace between label name and colon on line %d\n"

/* Assembly directives */
#define ERROR_WHITESPACE_BEFORE_DIRECTIVE "WARN: Whitespace before directive on line %d, whitespace ignored\n"

/* String parsing */
#define ERROR_UNPROCESSED_TEXT "ERROR: Excessive text" /* Line num is inserted here */
#define ERROR_NO_CURBRACE_AFTER_FORMAT "ERROR: !!!! No curly brace or type after format character !!!!\n"
#define ERROR_EXPECTED_CHARACTER "ERROR: Expected character '%c' in column %d" /* Line num is inserted here */
#define ERROR_UNEXPECTED_FMT_END "ERROR: !!!! Unexpected format string to end, missing closing '}' !!!!\n"

/* Turn on to get info on all lines */
#define DEBUG_MODE 1

#endif