cmake_minimum_required(VERSION 3.5)
project(LinkedList)

set(CMAKE_CXX_STANDARD 20)

include_directories(./include ./Tests)

add_executable(LinkedList
        src/main.cpp)