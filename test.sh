flex lexical_analysis.l
g++ lex.yy.c -lfl -std=c++14 -o test
./test