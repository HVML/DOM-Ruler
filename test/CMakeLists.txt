cmake_minimum_required(VERSION 3.10)

project(css_select_test)

# css
list(APPEND css_select_test_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/src/dom
    ${CMAKE_SOURCE_DIR}/src/select
)

list(APPEND css_select_test_SOURCES
    ${CMAKE_SOURCE_DIR}/test/css_select.c
)

include_directories(${css_select_test_INCLUDE_DIRECTORIES} ${HICSS_INCLUDE_DIRS})
link_directories(${HICSS_LIBRARY_DIRS})
add_executable(css_select_test ${css_select_test_SOURCES})
target_link_libraries(css_select_test hilayout)

list(APPEND css_select_test2_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/src/dom
    ${CMAKE_SOURCE_DIR}/src/select
)

list(APPEND css_select_test2_SOURCES
    ${CMAKE_SOURCE_DIR}/test/css_select2.c
)

include_directories(${css_select_test2_INCLUDE_DIRECTORIES} ${HICSS_INCLUDE_DIRS})
link_directories(${HICSS_LIBRARY_DIRS})
add_executable(css_select_test2 ${css_select_test2_SOURCES})
target_link_libraries(css_select_test2 hilayout)
