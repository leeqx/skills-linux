cmake_minimum_required(VERSION 2.8)
project(gcc_class_hierarchy)

set(CMAKE_CXX_STANDARD 14)
ADD_COMPILE_OPTIONS(-fdump-class-hierarchy)

add_executable(gcc_class_hierarchy main.cpp)