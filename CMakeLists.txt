cmake_minimum_required(VERSION 3.15)
project(FirstProject)

set(CMAKE_CXX_STANDARD 14)

#add_executable(FirstProject main.cpp Student.cpp Student.h)
add_executable(FirstProject Test/hello.cpp Student.h Student.cpp)