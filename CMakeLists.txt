cmake_minimum_required(VERSION 3.15)
project(FirstProject)

set(CMAKE_CXX_STANDARD 14)


#运行SortClass目录下的LinearSort.cpp
#add_executable(FirstProject SortClass/LinearSort.cpp)

#运行src目录下的main.cpp
#add_executable(FirstProject main.cpp)


#add_executable(FirstProject DSModel/Graph/MinSpanningTreeD.cpp DSModel/Graph/UFsets.h)
#add_executable(FirstProject DSModel/Graph/MinSpanningTreeM.cpp)

#add_executable(FirstProject STL/MinHeapByVector2.cpp)
#add_executable(FirstProject SortClass/LinearSort.cpp)



add_executable(FirstProject Chenhongy/Graph/GraphMatrix.cpp)