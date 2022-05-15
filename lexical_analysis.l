%{
#include "token.h"
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
vector<Token> token_stream;

int line = 0;
int col = 0;
//int pos_end;
%}

TOKEN_DIV \/
TOKEN_MOD %

TOKEN_LTE <=
TOKEN_GTE >=
TOKEN_ASSIGN =

TOKEN_OR \|\|

TOKEN_VOID void
TOKEN_CONST const
TOKEN_RETURN return
TOKEN_CONTINUE continue
TOKEN_BREAK break

DIGIT = DIGIT
LETTER = [a-zA-Z] //
HEX = HEX

TAB   //TODO
SPACE //TODO


TOKEN_FLOATPOINT  (((DIGIT*.DIGIT+|DIGIT+.)([eE][+-]?DIGIT+)?)|((DIGIT+)([eE][+-]?DIGIT+)))|((0x|0X)(((HEX*.HEX+)|(HEX+.))|(HEX+)))

%%
{TOKEN_DIV} {
    token_stream.emplace_back(TOKEN_DIV, line, col, 0,yytext);
    return TOKEN_DIV;}

{TOKEN_MOD} {
    token_stream.emplace_back(TOKEN_MOD,0,0,0,yytext);
    return TOKEN_MOD;}

{TOKEN_LTE} {
    token_stream.emplace_back(TOKEN_LTE,0,0,0,yytext);
    return TOKEN_LTE;}

{TOKEN_GTE} {
    token_stream.emplace_back(TOKEN_GTE,0,0,0,yytext);
    return TOKEN_GTE;}

{TOKEN_ASSIGN} {
    token_stream.emplace_back(TOKEN_ASSIGN,0,0,0,yytext);
    return TOKEN_ASSIGN;}

{TOKEN_OR} {
    Token token(TOKEN_DIV,0,0,0,yytext);
    token_stream.emplace_back(token);
    return TOKEN_OR;}

{TOKEN_VOID} {
    Token token(TOKEN_DIV,0,0,0,yytext);
    token_stream.emplace_back(token);
    return TOKEN_VOID;}

{TOKEN_CONST} {
    Token token(TOKEN_DIV,0,0,0,yytext);
    token_stream.emplace_back(token);
    return TOKEN_CONST;}

{TOKEN_RETURN} {
    Token token(TOKEN_DIV,0,0,0,yytext);
    token_stream.emplace_back(token);
    return TOKEN_RETURN;}

{TOKEN_CONTINUE} {
    Token token(TOKEN_DIV,0,0,0,yytext);
    token_stream.emplace_back(token);
    return TOKEN_CONTINUE;}

{TOKEN_BREAK} {
    Token token(TOKEN_DIV,0,0,0,yytext);
    token_stream.emplace_back(token);
    return TOKEN_BREAK;}

{TOKEN_FLOATPOINT} {
    Token token(TOKEN_DIV,0,0,0,yytext);
    token_stream.emplace_back(token);
    return TOKEN_FLOATPOINT;}

\n      line++;

%%

vector<Token>& lexical_analysis(const char *input_file){
    if(!(yyin = fopen(input_file,"r"))){
        cout << "[ERROR] No input file\n";
        exit(1);
    }

    while(yylex());
    for (auto & t : token_stream){
        cout << t.data.identifier << endl;
    }

    return token_stream;
}

int yywrap(){return 0;}

int main(int argc, char *argv[]){

    char *input_file;
    strcpy(input_file, "test.cc");

    if (argc == 2) {
        strcpy(input_file, argv[1]);
    }

    // yylex()是flex提供的词法分析例程,默认读取stdin
    lexical_analysis(input_file);
    return 0;
}
