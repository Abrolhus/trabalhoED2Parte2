cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(SOURCE_FILES
    folhaQuadTree.cpp
    folhaQuadTree.h
    quadTree.cpp
    quadTree.h)
# TODO: check if '.h's are really needed here
add_library(quadtree SHARED STATIC ${SOURCE_FILES})
