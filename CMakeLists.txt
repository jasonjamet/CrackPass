cmake_minimum_required(VERSION 3.3)
project(CrackPass)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lcrypt")

set(SOURCE_FILES
    main.cpp
    Functions.cpp
    Functions.h
    main.h
    README.md)

add_executable(CrackPass ${SOURCE_FILES})