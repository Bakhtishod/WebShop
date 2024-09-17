cmake_minimum_required(VERSION 3.27)
project(Assignment C)

set(CMAKE_C_STANDARD 11)

add_executable(Assignment main.c
        assistant.h
        assistant.c)
