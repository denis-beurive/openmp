cmake_minimum_required(VERSION 3.10)
project(openmp C)

set(CMAKE_C_STANDARD 99)
# -Wall: not accepted
set(CMAKE_C_FLAGS "-fopenmp")

add_executable(thread_id src/thread_id.c)
set_target_properties(
        thread_id
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        EXCLUDE_FROM_ALL off)


