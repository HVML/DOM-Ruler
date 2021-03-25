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
add_library(parserutils ${parserutils_SOURCES})

