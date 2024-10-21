cmake_minimum_required(VERSION 3.5.0)
project(Tema4-08 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(T4-08 main.cpp)

