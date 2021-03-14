cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(SOURCE_FILES
    ArvoreB.cpp
    ArvoreB.h
    ArvoreAVL.cpp
    ArvoreAVL.h
    NoAVL.h
    NoAVL.cpp
    NoB.h
    NoB.cpp
    auxiliar.h
    auxiliar.cpp)
# TODO: check if '.h's are really needed here
add_library(arvores SHARED STATIC ${SOURCE_FILES})
