cmake_minimum_required(VERSION 3.15)
project(FirstProject)

set(CMAKE_CXX_STANDARD 14)

#add_executable(FirstProject main.cpp Student.cpp Student.h)

#运行Sort目录下的LinearSort.cpp
add_executable(FirstProject Sort/LinearSort.cpp)

#运行src目录下的main.cpp
#add_executable(FirstProject main.cpp)