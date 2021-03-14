#!/bin/bash

if [ -z ${ROOT_DIR+x} ]; 
then 
    BASE_DIR=$(dirname $(readlink -f "$0"))
    OUTPUT_DIR=$BASE_DIR/output
    ROOT_DIR=$OUTPUT_DIR/root
    export CMAKE_INCLUDE_PATH="$ROOT_DIR/usr/include"
    export CMAKE_LIBRARY_PATH="$ROOT_DIR/usr/lib"
    export PKG_CONFIG_PATH="$ROOT_DIR/usr/lib/pkgconfig"
    mkdir -p $ROOT_DIR
fi

echo ""
echo "ROOT_DIR=$ROOT_DIR"
echo ""

cmake -DCMAKE_INSTALL_PREFIX=$ROOT_DIR/usr
#make VERBOSE=1
make

