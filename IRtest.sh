#!/usr/bin/env bash

if [ -d "./build" ]; then
    echo "directory \"./build\" exists"
    cd build || exit
    cmake ..
    make
else 
    mkdir build
    cd build || exit
    cmake ..
    make
fi

cp IRtest.out ../IRtest.out