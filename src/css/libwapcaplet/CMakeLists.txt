cmake_minimum_required(VERSION 3.10)

project(wapcaplet)
add_definitions(-fPIC)

list(APPEND wapcaplet_INCLUDE_DIRECTORIES
    include
    src
)

list(APPEND wapcaplet_SOURCES
    src/libwapcaplet.c
)

include_directories(${wapcaplet_INCLUDE_DIRECTORIES})
add_library(wapcaplet ${wapcaplet_SOURCES})


