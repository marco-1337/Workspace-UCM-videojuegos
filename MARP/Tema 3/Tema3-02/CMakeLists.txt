cmake_minimum_required(VERSION 3.15.0)
project(T3-02 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(Tema3-02 Tema3-02.cpp)
