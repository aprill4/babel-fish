#!/usr/bin/env bash
set -eu

mkdir -p build
# basd
g++ -std=c++17 babel.cc lex.yy.cpp syntax_analyzer.tab.cpp ast.cpp IR.cpp Dominators.cc Mem2Reg.cc LoopSearch.cc LoopInvHoist.cc arm.cpp RemoveRedundantLoad.cpp -o build/babel -g
