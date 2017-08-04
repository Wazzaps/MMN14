cmake_minimum_required(VERSION 3.7)
project(mmn14)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES src/main.c src/structures.c src/util_functions.c src/util_functions.h src/directive_parser.c src/directive_parser.h src/general_parsing.c src/general_parsing.h src/string_parser.c src/string_parser.h src/directive_functions.c src/directive_functions.h src/global_constants.h src/op_parser.c src/op_parser.h src/code.c src/code.h)
add_executable(mmn14 ${SOURCE_FILES})