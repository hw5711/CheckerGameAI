cmake_minimum_required(VERSION 3.15)
project(myVersion)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(myVersion
        AlphaBetaSearch.cpp
        AlphaBetaSearch.h
        Checker.cpp
        Checker.h
        GameTree.cpp
        GameTree.h
        main.cpp
        MinMaxAB.cpp
        MinMaxAB.h)
