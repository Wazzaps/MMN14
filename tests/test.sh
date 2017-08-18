#!/bin/bash

make

read -rsp $'Press enter to continue...\n'

cd tests/test_files

tests=(*)

for test in "${tests[@]}"
do
    clear
    echo "Testing $test..."
    echo "=============================="
    cd "$test"
    ../../../bin/assembler "$test"
    echo "Returned $?"
    echo "$test.ob:"
    cat "$test.ob"
    echo "$test.ent:"
    cat "$test.ent"
    echo "$test.ext:"
    cat "$test.ext"
    cd ../

    read -rsp $'Press enter to continue...\n'
done
