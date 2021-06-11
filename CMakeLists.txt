cmake_minimum_required(VERSION 3.10)
project(lox_interpreter)

#minimum C++ version
set(CMAKE_CXX_STANDARD 11)

#include header files
include_directories(lox/include)

#define source files
file(GLOB LOX_SRC ${CMAKE_CURRENT_LIST_DIR}/lox/src/*.cpp)
add_executable(lox ${LOX_SRC})
