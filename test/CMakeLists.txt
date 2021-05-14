#
# 
#                           IMPORTANT NOTICE
# 
#  The following open source license statement does not apply to any
#  entity in the Exception List published by FMSoft.
# 
#  For more information, please visit:
# 
#  https://www.fmsoft.cn/exception-list
# 
#
#   This file is part of HiDOMLayout. hiDOMLayout is a library to
#   maintain a DOM tree, lay out and stylize the DOM nodes by
#   using CSS (Cascaded Style Sheets).
#
#   Copyright (C) 2021 Beijing FMSoft Technologies Co., Ltd.
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU Lesser General License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU Lesser General License for more details.
#
#   You should have received a copy of the GNU Lesser General License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#   Or,
#
#   As this program is a library, any link to this program must follow
#   GNU Lesser General License version 3 (LLGPLv3). If you cannot accept
#   LLGPLv3, you need to be licensed from FMSoft.
#
#   If you have got a commercial license of this program, please use it
#   under the terms and conditions of the commercial license.
#
#   For more information about the commercial license, please refer to
#   <http://www.minigui.com/blog/minigui-licensing-policy/>.
#

cmake_minimum_required(VERSION 3.10)

project(css_select_test)
add_definitions(-D_DEBUG)

# node
list(APPEND node_test_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/css/libparserutils/include
    ${CMAKE_SOURCE_DIR}/src/css/libwapcaplet/include
    ${CMAKE_SOURCE_DIR}/src/css/libcss/include
    ${CMAKE_SOURCE_DIR}/src/layout/src
)

list(APPEND node_test_SOURCES
    ${CMAKE_SOURCE_DIR}/test/node_test.c
)

include_directories(${node_test_INCLUDE_DIRECTORIES} ${GLIB_INCLUDE_DIRS})
add_executable(node_test ${node_test_SOURCES})
target_link_libraries(node_test hidomlayout ${GLIB_LIBRARIES})

# css
list(APPEND css_select_test_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/css/libparserutils/include
    ${CMAKE_SOURCE_DIR}/src/css/libwapcaplet/include
    ${CMAKE_SOURCE_DIR}/src/css/libcss/include
    ${CMAKE_SOURCE_DIR}/src/layout/src
)

list(APPEND css_select_test_SOURCES
    ${CMAKE_SOURCE_DIR}/test/css_select.c
)

include_directories(${css_select_test_INCLUDE_DIRECTORIES} ${GLIB_INCLUDE_DIRS})
add_executable(css_select_test ${css_select_test_SOURCES})
target_link_libraries(css_select_test hidomlayout ${GLIB_LIBRARIES})

list(APPEND css_select_test2_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/css/libparserutils/include
    ${CMAKE_SOURCE_DIR}/src/css/libwapcaplet/include
    ${CMAKE_SOURCE_DIR}/src/css/libcss/include
    ${CMAKE_SOURCE_DIR}/src/layout/src
)

list(APPEND css_select_test2_SOURCES
    ${CMAKE_SOURCE_DIR}/test/css_select2.c
)

include_directories(${css_select_test2_INCLUDE_DIRECTORIES} ${GLIB_INCLUDE_DIRS})
add_executable(css_select_test2 ${css_select_test2_SOURCES})
target_link_libraries(css_select_test2 hidomlayout ${GLIB_LIBRARIES})


# layout_test
list(APPEND layout_test_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/include
)

list(APPEND layout_test_SOURCES
    ${CMAKE_SOURCE_DIR}/test/layout_test.c
)

include_directories(${layout_test_INCLUDE_DIRECTORIES} ${GLIB_INCLUDE_DIRS})
add_executable(layout_test ${layout_test_SOURCES})
target_link_libraries(layout_test hidomlayout ${GLIB_LIBRARIES})
