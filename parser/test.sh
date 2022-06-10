#!/usr/bin/env bash
bison -d syntax_analyzer.y
flex lexical_analyzer.l
g++ lex.yy.c syntax_analyzer.tab.c ast.cc check.cc -std=c++14 -o test
rm -f lex.yy.c syntax_analyzer.tab.c syntax_analyzer.tab.h