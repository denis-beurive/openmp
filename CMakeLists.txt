cmake_minimum_required(VERSION 3.10)
project(openmp C)

set(CMAKE_C_STANDARD 99)
# -Wall: not accepted
set(CMAKE_C_FLAGS "-fopenmp")

add_executable(parallel_section src/parallel_section.c)
set_target_properties(
        parallel_section
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        EXCLUDE_FROM_ALL off)

add_executable(loop_bloc_synchronisation src/loop_bloc_synchronisation.c)
set_target_properties(
        loop_bloc_synchronisation
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        EXCLUDE_FROM_ALL off)

add_executable(reduction src/reduction.c)
set_target_properties(
        reduction
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        EXCLUDE_FROM_ALL off)

