cmake_minimum_required(VERSION 3.10.0)
project(Tema7-01 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    "DijkstraIndirecto.h"
    "GrafoValorado.h"
    "IndexPQ.h"
)