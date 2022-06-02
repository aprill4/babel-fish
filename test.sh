#!/usr/bin/env bash
bison -d parse.y
flex token.l
g++ lex.yy.c parse.tab.c ast.cc -std=c++14 -o test