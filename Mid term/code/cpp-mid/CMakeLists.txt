cmake_minimum_required(VERSION 3.30)
project(cpp_mid)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_mid
        main.cpp
        AutoKey.cpp
        AutoKey.h
        VigenereIterator.h
        VigenereIterator.cpp
)
