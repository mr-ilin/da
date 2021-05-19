cmake_minimum_required(VERSION 3.19)
project(da_lab_08)

set(CMAKE_CXX_STANDARD 17)

add_executable(da_lab_08 main.cpp coins.h coins.cpp dp_coins.h dp_coins.cpp benchmark.cpp)