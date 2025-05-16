cmake_minimum_required(VERSION 3.10.0)
project(task_3 VERSION 0.1.0 LANGUAGES C CXX)

include_directories(../task_2)

add_executable(task_3 typeMap.h task_3.cpp)

