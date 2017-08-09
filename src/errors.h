#ifndef ERRORS_H
#define ERRORS_H

// TODO: Add file names to all errors

/* Files */
#define ERROR_NO_INPUT_FILES "ERROR: Missing input files\n"
#define ERROR_CANNOT_READ "ERROR: Cannot read the file: %s\n"
#define ERROR_CANNOT_WRITE "ERROR: Cannot write the file: %s\n"
#define ERROR_LINE_TOO_LONG "WARN: Line number %d longer than the max allowed (%d)\n"

/* Labels */
#define ERROR_EMPTY_LABEL "WARN: Empty label on line %d in file %s\n"
#define ERROR_USELESS_LABEL "WARN: Useless label, no directive or operation on line %d. Ignored\n"
#define ERROR_LABEL_TOO_LONG "ERROR: Labels must have a maximum of %d characters, Violation on line %d\n"
#define ERROR_LABEL_NOT_ON_START_OF_LINE "ERROR: Labels not at the start of the line on line %d in file %s, label ignored\n"
#define ERROR_WHITESPACE_AFTER_LABEL "ERROR: Whitespace between label name and colon on line %d in file %s, label ignored\n"
#define ERROR_LABEL_CANNOT_START_WITH_NUM "ERROR: Label name can't start with number on line %d in file %s, label ignored\n"
#define ERROR_LABEL_NAME_IDENTICAL_OP_NAME " ERROR: Label name can't be equal to op names on line %d in file %s, label ignored\n"
#define ERROR_LABEL_NAME_IDENTICAL_REG_MAME "ERROR: Label name can't be equal to register names on line %d in file %s, label ignored\n"
#define ERROR_LABEL_NAME_IDENTICAL_DIR_MAME "ERROR: Label name can't be equal to directive names on line %d in file %s, label ignored\n"
#define ERROR_LABEL_NAME_NOT_LETTER_OR_NUM "ERROR: ERROR: Label name include only letters and numbers. on line %d in file %s, label ignored\n"

/* Assembly directives */
#define ERROR_WHITESPACE_BEFORE_DIRECTIVE "WARN: Whitespace before directive on line %d, whitespace ignored\n"
#define ERROR_UNKNOWN_DIRECTIVE "ERROR: Unknown directive '%s' on line %d\n"
#define ERROR_DATA_OUT_OF_BOUNDS "ERROR: Value %d is out of bounds (-512..511) on line %d\n"
#define  ERROR_DATA_MISSING_COMMA "ERROR: Syntax error - missing comma in data line %d in file %s\n"
#define ERROR_DATA_IS_NOT_NUM "ERROR: Not only numbers in data on line %d in file %s\n"

/* OPs */
#define ERROR_UNKNOWN_OP "ERROR: Unknown OP name '%s' on line %d\n"
#define ERROR_MISSING_FIRST_OPERAND "ERROR: Invalid first operand on line %d in file %s\n"
#define ERROR_MISSING_SECOND_OPERAND "ERROR: Invalid second operand on line %d in file %s\n"

/* Parsing */
#define ERROR_EXPECTED_CHARACTER "ERROR: Expected '%c' but got '%c' (ASCII %d) on line %d in file %s\n"
#define ERROR_EXPECTED_CHARACTER_EOL "ERROR: Expected '%c' but line ended on line %d in file %s\n"
#define ERROR_EXPECTED_NUMBER "ERROR: Expected a number but got '%c' (ASCII %d) on line %d in file %s\n"
#define ERROR_EXPECTED_NUMBER_EOL "ERROR: Expected a number but line ended on line %d in file %s\n"
#define ERROR_EXPECTED_WHITESPACE "ERROR: Expected whitespace but got '%c' (ASCII %d) on line %d in file %s\n"
#define ERROR_MATRIX_DIMENSION_POSITIVE "ERROR: Matrix dimension must be positive on line %d in file %s\n"
#define ERROR_UNEXPECTED_TEXT "ERROR: Expected end of line, got \"%s\" on line %d in file %s\n"
#define ERROR_INVALID_OPERATOR "ERROR: Operand number is invalid,  on line %d in file %s\n"
#define ERROR_UNNECESSSARY_OPERATOR "ERROR: Unnecessay operator on line %d in file %s\n"

/* String parsing */
#define ERROR_UNPROCESSED_TEXT "ERROR: Excessive text on line %d\n"
#define ERROR_EXPECTED_WORD "ERROR: Expected a word on line %d\n"

#define ERROR_UNMATCHED_TYPES "ERROR: Couldn't match any of the following types on line %d:\n"
#define ERROR_UNMATCHED_TYPE "ERROR: Couldn't match \"%s\" on line %d\n"
#define ERROR_COMMA_AT_START "ERROR: Found ',' at start of comma-seperated array on line %d\n"
#define ERROR_UNEXPECTED_FMT_END "ERROR: Unexpected format string to end, missing closing '}'\n"
#define ERROR_NO_CURBRACE_AFTER_FORMAT "ERROR: No curly brace or type after format character\n"

/* General errors */
#define ERROR_OUT_OF_MEMORY "FATAL: OUT OF MEMORY!\n"

#endif