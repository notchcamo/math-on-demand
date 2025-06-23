cmake_minimum_required(VERSION 3.31)
project(soo)

set(CMAKE_CXX_STANDARD 20)

add_library(soo STATIC src/library.cpp)

# By notchcamo.

include_directories(include)
add_subdirectory(test)