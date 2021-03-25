cmake_minimum_required(VERSION 3.10)

project(css_select_test)
add_definitions(-D_DEBUG)

# node
list(APPEND node_test_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/css/libparserutils/include
    ${CMAKE_SOURCE_DIR}/src/css/libwapcaplet/include
    ${CMAKE_SOURCE_DIR}/src/css/libcss/include
    ${CMAKE_SOURCE_DIR}/src/layout
)

list(APPEND node_test_SOURCES
    ${CMAKE_SOURCE_DIR}/test/node_test.c
)

include_directories(${node_test_INCLUDE_DIRECTORIES} ${HICSS_INCLUDE_DIRS})
link_directories(${HICSS_LIBRARY_DIRS})
add_executable(node_test ${node_test_SOURCES})
target_link_libraries(node_test hilayout)

# css
list(APPEND css_select_test_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/css/libparserutils/include
    ${CMAKE_SOURCE_DIR}/src/css/libwapcaplet/include
    ${CMAKE_SOURCE_DIR}/src/css/libcss/include
    ${CMAKE_SOURCE_DIR}/src/layout
)

list(APPEND css_select_test_SOURCES
    ${CMAKE_SOURCE_DIR}/test/css_select.c
)

include_directories(${css_select_test_INCLUDE_DIRECTORIES} ${HICSS_INCLUDE_DIRS})
link_directories(${HICSS_LIBRARY_DIRS})
add_executable(css_select_test ${css_select_test_SOURCES})
target_link_libraries(css_select_test hilayout)

list(APPEND css_select_test2_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/css/libparserutils/include
    ${CMAKE_SOURCE_DIR}/src/css/libwapcaplet/include
    ${CMAKE_SOURCE_DIR}/src/css/libcss/include
    ${CMAKE_SOURCE_DIR}/src/layout
)

list(APPEND css_select_test2_SOURCES
    ${CMAKE_SOURCE_DIR}/test/css_select2.c
)

include_directories(${css_select_test2_INCLUDE_DIRECTORIES} ${HICSS_INCLUDE_DIRS})
link_directories(${HICSS_LIBRARY_DIRS})
add_executable(css_select_test2 ${css_select_test2_SOURCES})
target_link_libraries(css_select_test2 hilayout)


# layout_test
list(APPEND layout_test_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/css/libparserutils/include
    ${CMAKE_SOURCE_DIR}/src/css/libwapcaplet/include
    ${CMAKE_SOURCE_DIR}/src/css/libcss/include
    ${CMAKE_SOURCE_DIR}/src/layout
)

list(APPEND layout_test_SOURCES
    ${CMAKE_SOURCE_DIR}/test/layout_test.c
)

include_directories(${layout_test_INCLUDE_DIRECTORIES} ${HICSS_INCLUDE_DIRS})
link_directories(${HICSS_LIBRARY_DIRS})
add_executable(layout_test ${layout_test_SOURCES})
target_link_libraries(layout_test hilayout)
