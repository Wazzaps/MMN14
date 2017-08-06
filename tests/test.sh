#!/bin/bash

cd test_files

tests=(*)

for test in "${tests[@]}"
do
    clear
    echo "Testing $test..."
    echo "=============================="
    rm ../temp/*
    cp $test ../temp
    cd ../temp
    ../../cmake-build-debug/mmn14 ${test::-3}
    echo $?
    cd ../test_files

    read -rsp $'Press enter to continue...\n'
done
