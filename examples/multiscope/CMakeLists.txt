cmake_minimum_required(VERSION 3.5)
project(multiscope C CXX)

set(CMAKE_CXX_STANDARD 11)
include(../CMakeLists.cmake.in)
include(../examples.cmake.in)

teensy_add_executable(multiscope multiscope.cpp)
#set(CMAKE_VERBOSE_MAKEFILE 1)