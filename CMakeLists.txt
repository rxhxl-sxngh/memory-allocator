cmake_minimum_required(VERSION 3.20)
project(custom_allocator C)

set(CMAKE_C_STANDARD 11)

include(CTest)
add_executable(custom_allocator src/main.c src/alloc.c)
