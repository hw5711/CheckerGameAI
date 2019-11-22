cmake_minimum_required(VERSION 3.15)
project(CheckerGameAI)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CheckerGameAI
        AlphaBeta.cpp
        AlphaBeta.h
        Checker.cpp
        Checker.h
        CheckerTree.cpp
        CheckerTree.h
        main.cpp
        MinMaxAB.cpp
        MinMaxAB.h Object.h)
