cmake_minimum_required(VERSION 3.19)
project(cp_da)

set(CMAKE_CXX_STANDARD 17)

add_executable(cp_da src/main.cpp src/lzw.h src/lzw.cpp)
add_executable(cp_da_test src/lzw.h src/lzw.cpp test/unit_tests.cpp)