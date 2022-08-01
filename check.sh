#!/usr/bin/env bash
set -eu

#bison -d syntax_analyzer.y
#flex lexical_analyzer.l

if [ -d "./build" ]; then
    echo "directory \"./build\" exists"
    cd build || exit
    cmake ..
    make -j$(nproc)
else 
    mkdir build
    cd build || exit
    cmake ..
    make -j$(nproc)
fi

cp check.out ../check.out
