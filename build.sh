#!/usr/bin/env bash
set -eu

mkdir -p build
# basd
g++ babel.cc lex.yy.cpp syntax_analyzer.tab.cpp ast.cpp IR.cpp arm.cpp RemoveRedundantLoad.cpp -o build/babel -g
