cmake_minimum_required(VERSION 3.4)
project(IPP_1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wall")

set(SOURCE_FILES
        hospital.c
        parse.c
        parse.h
        structure.c
        structure.h)
add_executable(IPP_1 ${SOURCE_FILES})