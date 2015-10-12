cmake_minimum_required(VERSION 3.3)
project(CrackPass)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lcrypt -O3 -I/usr/lib/openmpi/include -I/usr/lib/openmpi/include/openmpi -pthread -L/usr//lib -L/usr/lib/openmpi/lib -lmpi_cxx -lmpi -ldl -lhwloc
")

set(SOURCE_FILES
        QT/Crack/Functions.h
    main.cpp
        QT/Crack/Functions.cpp
    shadow)

add_executable(CrackPass ${SOURCE_FILES})
