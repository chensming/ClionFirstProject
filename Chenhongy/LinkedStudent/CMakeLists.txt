cmake_minimum_required(VERSION 3.15)
project(LinkedStudent)

set(CMAKE_CXX_STANDARD 14)

#在LinkedStudent单独的项目中
add_executable(LinkedStudent main.cpp studentUnit.h studentUnit.cpp)

#在FirstProject项目中
#add_executable(FirstProject Chenhongy/LinkedStudent/studentUnit.h
#        Chenhongy/LinkedStudent/studentUnit.cpp Chenhongy/LinkedStudent/main.cpp)