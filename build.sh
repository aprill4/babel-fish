#!/usr/bin/env bash
set -eu

mkdir -p build
g++ -std=c++17 babel.cc lex.yy.cpp syntax_analyzer.tab.cpp ast.cpp IR.cpp Dominators.cc Mem2Reg.cc LoopSearch.cc LoopInvHoist.cc arm.cpp remove_redundant_loads.cpp remove_identical_mvs.cpp -o build/babel -g
