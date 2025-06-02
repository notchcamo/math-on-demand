cmake_minimum_required(VERSION 3.31)
project(math_on_demand)

set(CMAKE_CXX_STANDARD 20)

add_library(math_on_demand STATIC src/library.cpp)

# By notchcamo.

include_directories(include)
add_subdirectory(test)