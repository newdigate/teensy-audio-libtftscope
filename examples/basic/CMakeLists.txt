cmake_minimum_required(VERSION 3.5)
project(basic C CXX)

set(CMAKE_CXX_STANDARD 11)
include(../CMakeLists.cmake.in)
include(../examples.cmake.in)

teensy_add_executable(basic basic.cpp)
#set(CMAKE_VERBOSE_MAKEFILE 1)