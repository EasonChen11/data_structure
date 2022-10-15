cmake_minimum_required(VERSION 3.22)
project(data_structure C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab03a Lab03a.c)
add_executable(Lab03b clock.c)
add_executable(data data_gen.c)
add_executable(timespec Lab03b.c)
