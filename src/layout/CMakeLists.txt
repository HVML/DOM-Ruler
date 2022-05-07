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
#   GNU Lesser General License version 3 (LGPLv3). If you cannot accept
#   LGPLv3, you need to be licensed from FMSoft.
#
#   If you have got a commercial license of this program, please use it
#   under the terms and conditions of the commercial license.
#
#   For more information about the commercial license, please refer to
#   <http://www.minigui.com/blog/minigui-licensing-policy/>.
#

cmake_minimum_required(VERSION 3.10)

project(hidomlayout VERSION 1.0.0)

#add_definitions(-D_DEBUG)

list(APPEND hidomlayout_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/css/libparserutils/include
    ${CMAKE_SOURCE_DIR}/src/css/libwapcaplet/include
    ${CMAKE_SOURCE_DIR}/src/css/libcss/include
    ${CMAKE_SOURCE_DIR}/src/layout/src
)

list(APPEND hidomlayout_SOURCES
    src/node.c
    src/select.c
    src/utils.c
    src/layout.c
    src/layout_block.c
    src/layout_inline_block.c
    src/layout_grid.c
    src/hl_dom_element_node.c
)

include_directories(${hidomlayout_INCLUDE_DIRECTORIES} ${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARIES})
add_library(hidomlayout SHARED ${hidomlayout_SOURCES})
set_target_properties(hidomlayout PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR})
target_link_libraries(hidomlayout css  ${PURC_LIBRARIES})


configure_file(hidomlayout.pc.in hidomlayout.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/hidomlayout.pc DESTINATION lib/pkgconfig)
install(FILES ${CMAKE_SOURCE_DIR}/include/hidomlayout.h DESTINATION include)
install(TARGETS hidomlayout DESTINATION lib)
