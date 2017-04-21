# MMN14
Assembler for university course 

# Building and testing
There is a custom makefile with the following commands:
* `make` - `compile`, `compiletests`, and `test`
* `make compile` - Only compiles everything from `src/` to `obj/` and links to `bin/mycompiler`
* `make compiletests` - Compiles all unit tests from `unittests_src` to `unittests_obj` and links each one individually with everything from `obj` except `main.o` into executables at `unittests_bin`
* `make test` - Executes all executables from `unittests_bin` and all shell scripts from `integrationtests` and checks for failed tests
* `make clean` - Deletes all executable and object files, required to be run before commits
* `make setup-precommit` - Sets up a hook that disallows commits if they fail compilation or any tests. Very recommended
* `make unsetup-precommit` - Removes the hook

# Style guide
* Tabs for indentation, spaces for alignment. Tab width does not matter. I use 4.
* Function declarations and defenitions: spaces after name, pointer star adjacent to type. Curly brace one space after argument list, not on new line.
```c
int abc (int a, char* b);

int abc (int a, char* b) {
    ...
}
```
* Function names are either `modulename_long_func_name_here` for "public" function or `modulename__long_func_name_here` for "private" functions (note the double underscore).
* Public functions' declarations are in the file's corresponding header file, private functions' declarations are in the c file and are **static**.

# The Assembly language
Values can be passed to operations in 4 methods:

| Method        | Example             | Explanation                                                                                  |
| ------------- | ------------------- | -------------------------------------------------------------------------------------------- |
| Constant      | `mov #-1, r2`       | The number `-1` is put in `r2`.                                                              |
| Label         | `mov a, r2`         | The value in the memory location defined by `a` is copied to `r2`.                           |
| Register      | `mov r3, r2`        | The value in `r3` is copied to `r2`.                                                         |
| Matrix access | `mov a[r5][r6], r2` | Copies the value in matrix `a` at row number `valueof(r5)` and column `valueof(r6)` to `r2`. |

The op table is as follows: (Note that "B" cannot be a constant, obviously)

| OP code | OP name | Full name / What it means |
| --- | --- | --- |
| 0 | `mov A, B` | Copies from A to B |
| 1 | `cmp A, B` | If A == B, then sets the Z[ero] bit on the PSW, else clears |
| 2 | `add A, B` | B = B + A |
| 3 | `sub A, B` | B = B - A |
| 4 | `not A` | Bitwise NOT |
| 5 | `clr A` | A = 0 |
| 6 | `lea A, B` | B = Address defined by label A |
| 7 | `inc A` | A++ |
| 8 | `dec A` | A-- |
| 9 | `jmp A` | P[rogram]C[ounter] = A |
| 10 | `bne A` | If Z != 0, then PC = A |
| 11 | `red A` | A = one character from stdin |
| 12 | `prn A` | Print one character stored in A |
| 13 | `jsr A` | Push PC, jmp A (jump to subroutine) |
| 14 | `rts` | Pop PC (return) |
| 15 | `stop` | Stop execution |

The max length of a line is 80 characters (not including `\n`).

There are 4 statement types:

| Type        | Explanation                                                               |
| ----------- | ------------------------------------------------------------------------- |
| Whitespace  | Line containing only spaces and tabs                                      |
| Comment     | Line begins with a `';'`, ignored                                         |
| Guidance    | Memory allocation, and other compile-time things for the asssembler to do |
| Instruction | Literal instruction to be decoded                                         |

There are 5 guidance types:

| Type    | Example                               | Explanation                                                                                                    |
| ------- | ------------------------------------- | -------------------------------------------------------------------------------------------------------------- |
| .data   | `MYNUMBER: .data 5, +2, -7`           | Memory is allocated for three integers, and the address of the first integer stored as `MYNUMBER`              |
| .string | `MYNAME: .string "Moshe"`             | Memory is allocated for 6 chars, one for each character and one `\0` character                                 |
| .mat    | `MYMAT: .mat [2][3] 1, 1, 1, 2, 2, 2` | Memory is allocated for 6 integers. They are accessed by `[row][col]`. Init numbers are optional.              |
| .entry  | `.entry MYCOSINE`                     | An instruction for the linker that this label is a coroutine that can be used by other files                   |
| .extern | `.extern MYCOSINE`                    | An instruction for the linker that there exists an `.entry` declaration in another file, and we want to use it |

An instruction statement is composed of the following:
* An optional label
* OP name (lowercase)
* Whitespace
* Operands seperated by commas

