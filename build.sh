#!/usr/bin/env bash
set -eu

mkdir -p build
# basd
clang++ babel.cc lex.yy.cpp syntax_analyzer.tab.cpp ast.cpp IR.cpp arm.cpp -o build/babel -g
