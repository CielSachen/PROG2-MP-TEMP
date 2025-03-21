cmake_minimum_required(VERSION 3.15...3.31)

project(PROG2MachineProject VERSION 1.0.0 DESCRIPTION "A Simple CLI-based Translator." LANGUAGES C)

set(CMAKE_C_STANDARD 99)

add_compile_options(-Wall -Werror -Wextra -Wpedantic -O2)

set(HEADER_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(lib)
add_subdirectory(src)
