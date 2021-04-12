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
#   This file is part of HybridOS, a developing operating system based on
#   MiniGUI. HybridOs will support embedded systems and smart IoT devices.
#
#   Copyright (C) 2020 Beijing FMSoft Technologies Co., Ltd.
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#   Or,
#
#   As this program is a library, any link to this program must follow
#   GNU General Public License version 3 (GPLv3). If you cannot accept
#   GPLv3, you need to be licensed from FMSoft.
#
#   If you have got a commercial license of this program, please use it
#   under the terms and conditions of the commercial license.
#
#   For more information about the commercial license, please refer to
#   <http://www.minigui.com/blog/minigui-licensing-policy/>.
#

cmake_minimum_required(VERSION 3.10)

project(hidomlayout)

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
)

include_directories(${hidomlayout_INCLUDE_DIRECTORIES} ${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARIES})
add_library(hidomlayout SHARED ${hidomlayout_SOURCES})
target_link_libraries(hidomlayout css)

configure_file(hidomlayout.pc.in hidomlayout.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/hidomlayout.pc DESTINATION lib/pkgconfig)
install(FILES ${CMAKE_SOURCE_DIR}/include/hidomlayout.h DESTINATION include)
install(TARGETS hidomlayout DESTINATION lib)
