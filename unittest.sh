#!/bin/bash
rm -rf db
g++ tests/main.cpp \
    tests/create_test.cpp \
    src/create/create.cpp \
    src/helper/helper.cpp \
    -o ./build/run_tests

./build/run_tests
./clean.sh
