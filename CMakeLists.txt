cmake_minimum_required(VERSION 3.16)
project(pcodeGen C CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(pcodeGen
        src/main.cpp
        src/miny.tab.cpp
        src/lex.yy.c)
target_include_directories(pcodeGen PRIVATE src)
