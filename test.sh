#!/usr/bin/env bash
bison -d parse.y
flex token.l
g++ lex.yy.c parse.tab.c ast.cc check.cc -std=c++14 -o test
rm -f lex.yy.c parse.tab.c parse.tab.h