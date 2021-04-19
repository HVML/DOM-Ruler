#!/bin/bash

if [ -z ${ROOT_DIR+x} ]; 
then 
    BASE_DIR=$(dirname $(readlink -f "$0"))
    OUTPUT_DIR=$BASE_DIR/output
    ROOT_DIR=$OUTPUT_DIR/root
    export CMAKE_INCLUDE_PATH="$ROOT_DIR/usr/local/include"
    export CMAKE_LIBRARY_PATH="$ROOT_DIR/usr/local/lib"
    export PKG_CONFIG_PATH="$ROOT_DIR/usr/local/lib/pkgconfig"
    mkdir -p $ROOT_DIR
fi

echo ""
echo "ROOT_DIR=$ROOT_DIR"
echo ""

cmake -DCMAKE_INSTALL_PREFIX=$ROOT_DIR/usr/local
#make VERBOSE=1
make

