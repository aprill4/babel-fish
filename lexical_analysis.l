%{
#include "token.h"
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
vector<Token> token_stream;
int line;
int pos_start;
int pos_end;
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

TOKEN_FLOATPOINT  ((([0-9]*.[0-9]+|[0-9]+.)([eE][+-]?[0-9]+)?)|(([0-9]+)([eE][+-]?[0-9]+)))|((0x|0X)((([0-9a-fA-F]*.[0-9a-fA-F]+)|([0-9a-fA-F]+.))|([0-9a-fA-F]+))([pP][+-]?[0-9]+))
%%
{TOKEN_DIV} {
    token_stream.emplace_back(TOKEN_DIV,0,0,0,yytext);
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
int main(){
    // yylex()是flex提供的词法分析例程,默认读取stdin
    lexical_analysis("test.cc");
    return 0;
}