cmake_minimum_required(VERSION 3.10)

project(examples)

# css
list(APPEND examples_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/libparserutils/include
    ${CMAKE_SOURCE_DIR}/libwapcaplet/include
    ${CMAKE_SOURCE_DIR}/libcss/include
)

list(APPEND examples_SOURCES
    ${CMAKE_SOURCE_DIR}/libcss/examples/example1.c
)

include_directories(${examples_INCLUDE_DIRECTORIES})
add_executable(examples ${examples_SOURCES})
target_link_libraries(examples hicss)
