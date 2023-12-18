cmake_minimum_required(VERSION 3.26)
project(schedular C)

set(CMAKE_C_STANDARD 11)

add_executable(schedular
        schedular.jjbush.c
        pqueue.jjbush.c
)
 