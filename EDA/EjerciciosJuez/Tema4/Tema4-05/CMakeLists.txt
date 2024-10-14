cmake_minimum_required(VERSION 3.5.0)
project(T4-05 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(T4-05 T4-05.cpp)

