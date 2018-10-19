cmake_minimum_required(VERSION 3.12)
project(solver)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        common/ArgumentsReader.cpp common/ArgumentsReader.h common/PuzzleReader.cpp common/PuzzleReader.h)

add_executable(solver ${SOURCE_FILES})