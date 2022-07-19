#!/usr/bin/env bash
set -eu

bison -d syntax_analyzer.y
flex lexical_analyzer.l

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

cp check.out ../check.out
