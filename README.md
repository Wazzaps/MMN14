# MMN14
C compiler for the imaginary assembly language defined by the university course

# Building and testing
There is a custom makefile with the following commands:
* `make` - `compile`, `compiletests`, and `test`
* `make compile` - Only compiles everything from `src/` to `obj/` and links to `bin/mycompiler`
* `make compiletests` - Compiles all unit tests from `unittests_src` to `unittests_obj` and links each one individually with everything from `obj` except `main.o` into executables at `unittests_bin`
* `make test` - Executes all executables from `unittests_bin` and all shell scripts from `integrationtests` and checks for failed tests
* `make clean` - Deletes all executable and object files, required to be run before commits
* `make setup-precommit` - Sets up a hook that disallows commits if they fail compilation or any tests. Very recommended
* `make unsetup-precommit` - Removes the hook