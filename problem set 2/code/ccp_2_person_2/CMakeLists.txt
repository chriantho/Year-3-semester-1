cmake_minimum_required(VERSION 3.30)
project(ccp_2_person_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(ccp_2_person_2
        FibonacciSequence.h
        FibonacciSequence.cpp
        FibonacciSequenceIterator.cpp
        main.cpp
)
