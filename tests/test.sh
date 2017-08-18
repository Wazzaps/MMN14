#!/bin/bash

cd test_files

tests=(*)

for test in "${tests[@]}"
do
    clear
    echo "Testing $test..."
    echo "=============================="
    cd "$test"
    valgrind --leak-check=yes ../../../cmake-build-debug/mmn14 "$test"
    ../../../cmake-build-debug/mmn14 "$test" 1> "$test.stdout" 2> "$test.stderr"
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
