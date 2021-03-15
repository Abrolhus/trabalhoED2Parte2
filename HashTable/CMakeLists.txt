cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(SOURCE_FILES
    HashTable.cpp)
add_library(hashtable SHARED STATIC ${SOURCE_FILES})
