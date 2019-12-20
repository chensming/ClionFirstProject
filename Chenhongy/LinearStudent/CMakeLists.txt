cmake_minimum_required(VERSION 3.15)
project(LinearStudent)

set(CMAKE_CXX_STANDARD 14)

#在LinearStudent单独的项目中
add_executable(LinearStudent studUnit.h studUnit.cpp main.cpp)

