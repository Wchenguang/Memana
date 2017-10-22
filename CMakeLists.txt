cmake_minimum_required(VERSION 3.8)
project(Memana)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        Memana.h
        BasePool.h
        )

add_executable(Memana ${SOURCE_FILES})