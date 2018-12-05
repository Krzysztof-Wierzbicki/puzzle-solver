cmake_minimum_required(VERSION 3.12)
project(solver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "-Ofast -g3")

set(SOURCE_FILES
        util/ArgParse.cpp
        util/ArgParse.h
        main.cpp
        Direction.h
        Fifteen.cpp
        Fifteen.h
        util/Timer.h
        Solver.cpp
        Solver.h
        Direction.cpp)

include_directories(CMAKE_CURRENT_SOURCE_DIR)

add_executable(solver ${SOURCE_FILES})