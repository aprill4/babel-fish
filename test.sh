set -v
flex lexical_analysis.l
g++ lex.yy.c -std=c++14 -o test
./test $1 > tokens
