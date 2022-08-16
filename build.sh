#!/usr/bin/env bash
set -eu

mkdir -p build
g++ -std=c++17 babel.cc lex.yy.cpp syntax_analyzer.tab.cpp ast.cpp IR.cpp Dominators.cc Mem2Reg.cc Gvn_Gcm.cc LoopSearch.cc LoopInvHoist.cc arm.cpp RemoveRedundantLoad.cpp -o build/babel -g
