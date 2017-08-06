cmake_minimum_required(VERSION 3.7)
project(mmn14)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES src/base4.c src/base4.h src/constant_data.c src/constant_data.h src/cpu_word.c src/cpu_word.h src/errors.h src/list.c src/list.h src/main.c src/parse_directives.c src/parse_directives.h src/parse_ops.c src/parse_ops.h src/parsing.c src/parsing.h src/state.h src/util_funcs.c src/util_funcs.h)
add_executable(mmn14 ${SOURCE_FILES})
