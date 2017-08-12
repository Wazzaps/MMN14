#!/bin/bash

cd test_files

tests=(*)

for test in "${tests[@]}"
do
    clear
    echo "Testing $test..."
    echo "=============================="
    cd "$test"
    ../../../cmake-build-debug/mmn14 "$test"
    echo "Returned $?"
    cd ../

    read -rsp $'Press enter to continue...\n'
done
