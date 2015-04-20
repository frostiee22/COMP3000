cmake_minimum_required(VERSION 3.1)
project(CProgramming)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c)
add_executable(CProgramming ${SOURCE_FILES} main.c years/2014-3.h years/2014-2.h library/heap.h)
