cmake_minimum_required(VERSION 3.8)
project(hgraph2_v2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        HGraph.cpp
        HGraph.h
        List.cpp
        List.h
        main.cpp
        SubList.cpp
        SubList.h)

add_executable(hgraph2_v2 ${SOURCE_FILES})