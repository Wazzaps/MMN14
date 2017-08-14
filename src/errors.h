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
#define ERROR_USELESS_LABEL "WARN: Useless label '%s', no directive or operation on line %d in file %s\n"
#define ERROR_LABEL_NOT_ON_START_OF_LINE "ERROR: Labels not at the start of the line on line %d in file %s, label ignored\n"
#define ERROR_WHITESPACE_AFTER_LABEL "ERROR: Whitespace between label name and colon on line %d in file %s, label ignored\n"
#define ERROR_LABEL_CANNOT_START_WITH_NUM "ERROR: Label name can't start with number on line %d in file %s\n"
#define ERROR_LABEL_NAME_IDENTICAL_OP_NAME "ERROR: Label name can't be equal to op names on line %d in file %s\n"
#define ERROR_LABEL_NAME_IDENTICAL_REG_MAME "ERROR: Label name can't be equal to register names on line %d in file %s\n"
#define ERROR_LABEL_NAME_IDENTICAL_DIR_MAME "ERROR: Label name can't be equal to directive names on line %d in file %s\n"
#define ERROR_LABEL_NAME_NOT_LETTER_OR_NUM "ERROR: Label names must be alphanumeric, violation on line %d in file %s\n"
#define ERROR_LABEL_DOESNT_EXIST "ERROR: Label \"%s\" does not exist on line %d in file %s\n"

/* Assembly directives */
#define ERROR_EMPTY_DIRECTIVE "ERROR: Empty directive on line %d in file %s\n"
#define ERROR_UNKNOWN_DIRECTIVE "ERROR: Unknown directive '%s' on line %d in file %s\n"
#define ERROR_DATA_OUT_OF_BOUNDS "ERROR: Value %ld is out of bounds (%d..%d) on line %d in file %s\n"
#define ERROR_INVALID_ENTRY "ERROR: Entry directive value is invalid on line %d in file %s\n"
#define ERROR_INVALID_EXTERN "ERROR: Extern directive value is invalid on line %d in file %s\n"

/* OPs */
#define ERROR_UNKNOWN_OP "ERROR: Unknown OP name '%s' on line %d in file %s\n"
#define ERROR_MISSING_FIRST_OPERAND "ERROR: Invalid first operand on line %d in file %s\n"
#define ERROR_MISSING_SECOND_OPERAND "ERROR: Invalid second operand on line %d in file %s\n"
#define ERROR_CODE_LABEL_IN_MATRIX "ERROR: Label \"%s\" pointing to code found in matrix on line %d in file %s\n"
#define ERROR_UNSUPPORTED_OPERAND_TYPE "ERROR: This instruction (%s) does not support this type of operator (%s) on line %d in file %s\n"

/* Parsing */
#define ERROR_EXPECTED_CHARACTER "ERROR: Expected '%c' but got '%c' (ASCII %d) on line %d in file %s\n"
#define ERROR_EXPECTED_CHARACTER_EOL "ERROR: Expected '%c' but line ended on line %d in file %s\n"
#define ERROR_EXPECTED_ANY_CHARACTER_EOL "ERROR: Expected a character but line ended on line %d in file %s\n"
#define ERROR_EXPECTED_NUMBER "ERROR: Expected a number but got '%c' (ASCII %d) on line %d in file %s\n"
#define ERROR_EXPECTED_NUMBER_EOL "ERROR: Expected a number but line ended on line %d in file %s\n"
#define ERROR_EXPECTED_WHITESPACE "ERROR: Expected whitespace but got '%c' (ASCII %d) on line %d in file %s\n"
#define ERROR_EXPECTED_EOL "ERROR: Expected end of line, got \"%s\" on line %d in file %s\n"
#define ERROR_MATRIX_DIMENSION_POSITIVE "ERROR: Matrix dimension %ld must be positive on line %d in file %s\n"
#define ERROR_MATRIX_DIMENSION_OUT_OF_BOUNDS "ERROR: Matrix dimension %ld is out of bounds (1..1024) on line %d in file %s\n"
#define ERROR_REGISTER_OUT_OF_BOUNDS "ERROR: Register number %ld is out of bounds (%d..%d) on line %d in file %s\n"
#define ERROR_LABEL_EXISTS "ERROR: Label \"%s\" already exists on line %d in file %s\n"
#define ERROR_EXTERN_EXIST "ERROR: Extern \"%s\" already exists on line %d in file %s\n"


/* General errors */
#define ERROR_OUT_OF_MEMORY "FATAL: OUT OF MEMORY!\n"

#endif