#!/usr/bin/env bash
set -eu

#bison -d syntax_analyzer.y
#flex lexical_analyzer.l

cmake -S . -B build
cmake --build build -j 8

