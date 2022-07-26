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
#   This file is part of DOM Ruler. DOM Ruler is a library to
#   maintain a DOM tree, lay out and stylize the DOM nodes by
#   using CSS (Cascaded Style Sheets).
#
#   Copyright (C) 2021 Beijing FMSoft Technologies Co., Ltd.
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

project(parserutils)
add_definitions(-fPIC)

list(APPEND parserutils_INCLUDE_DIRECTORIES
    include
    src
)

list(APPEND parserutils_SOURCES
    src/charset/aliases.c
    src/charset/codecs/codec_utf8.c
    src/charset/codecs/codec_ext8.c
    src/charset/codecs/codec_utf16.c
    src/charset/codecs/codec_ascii.c
    src/charset/codecs/codec_8859.c
    src/charset/encodings/utf8.c
    src/charset/encodings/utf16.c
    src/charset/codec.c
    src/input/inputstream.c
    src/input/filter.c
    src/utils/errors.c
    src/utils/buffer.c
    src/utils/vector.c
    src/utils/stack.c
)

include_directories(${parserutils_INCLUDE_DIRECTORIES})
add_library(parserutils STATIC ${parserutils_SOURCES})

