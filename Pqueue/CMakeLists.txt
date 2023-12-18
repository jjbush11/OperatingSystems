cmake_minimum_required(VERSION 3.26)
project(assignment2Pqu C)

set(CMAKE_C_STANDARD 11)

add_executable(assignment2Pqu
        pqueue.jjbush.c
        pqueue.jjbush.h
        pqueue-tests.c)
