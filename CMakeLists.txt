cmake_minimum_required(VERSION 3.3)
project(CrackPass)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lcrypt -O3")

set(SOURCE_FILES
    Functions.h
    main.cpp
    Functions.cpp
    shadow)

add_executable(CrackPass ${SOURCE_FILES})