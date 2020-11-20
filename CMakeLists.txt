cmake_minimum_required(VERSION 3.5)
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

add_executable(sections src/sections.c)
set_target_properties(
        sections
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        EXCLUDE_FROM_ALL off)

add_executable(collapse src/collapse.c)
set_target_properties(
        collapse
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        EXCLUDE_FROM_ALL off)

add_executable(breaker src/breaker_for_omp.c)
target_link_libraries(breaker crypt m)
set_target_properties(
        breaker
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        EXCLUDE_FROM_ALL off)
