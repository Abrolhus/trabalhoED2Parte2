cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_subdirectory(ArvoresBalanceadas)
add_subdirectory(LeituraArvoreQuad)
add_subdirectory(HashTable)

add_executable(trab
    Registro.cpp
    Interface.cpp
    main.cpp)

target_link_libraries(trab quadtree hashtable arvores)
