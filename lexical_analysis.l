%option noyywrap
%{
#include "token.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include<string.h>
#include<cstdlib>
using namespace std;

vector<Token> token_stream;

int line = 1;
int col = 1;
//int pos_end;
%}

TOKEN_ADD +
TOKEN_SUB -
TOKEN_MUL *
TOKEN_DIV \/
TOKEN_MOD %

TOKEN_EQ ==
TOKEN_NEQ !=
TOKEN_LT <
TOKEN_GT >
TOKEN_LTE <=
TOKEN_GTE >=
TOKEN_ASSIGN =

TOKEN_NOT !
TOKEN_AND && //escape?
TOKEN_OR \|\|

TOKEN_IF if
TOKEN_ELSE else
TOKEN_WHILE while
TOKEN_INT int
TOKEN_FLOAT float
TOKEN_VOID void
TOKEN_CONST const
TOKEN_RETURN return
TOKEN_CONTINUE continue
TOKEN_BREAK break

TOKEN_SEMICOLON ;
TOKEN_COMMA ,
TOKEN_LEFT_PARENTHESES (
TOKEN_RIGHT_PARENTHESES )
TOKEN_LEFT_BRACKETS [
TOKEN_RIGHT_BRACKETS ]
TOKEN_LEFT_BRACES {
TOKEN_RIGHT_BRACES }

TAB [\t]
SPACE [ ]
NEWLINE [\n]

NONZERO_DIGIT [1-9]
DIGIT [0-9]

HEX_PREFIX (0x)|(0X)
HEX_DIGIT [0-9a-fA-Z]

OCT_PREFIX 0
OCT_DIGIT [0-7]

DEC_CONST {NONZERO_DIGIT}{DIGIT}*
OCT_CONST {OCT_PREFIX}{OCT_DIGIT}*
HEX_CONST {HEX_PREFIX}{HEX_DIGIT}*

TOKEN_FLOATPOINT  (((DIGIT*.DIGIT+|DIGIT+.)([eE][+-]?DIGIT+)?)|((DIGIT+)([eE][+-]?DIGIT+)))|(HEX_PREFIX(((HEX_DIGIT*.HEX_DIGIT+)|(HEX_DIGIT+.))|(HEX_DIGIT+)))

LETTER [a-zA-Z]
TOKEN_IDENTIFIER ({LETTER}|_){DIGIT}|({LETTER}|_)*

%%
{TOKEN_DIV} {
    token_stream.emplace_back(TOKEN_DIV, line, col, yytext);
    return TOKEN_DIV;}

{TOKEN_MOD} {
    token_stream.emplace_back(TOKEN_MOD, line, col, yytext);
    return TOKEN_MOD;}

{TOKEN_LTE} {
    token_stream.emplace_back(TOKEN_LTE, line, col, yytext);
    return TOKEN_LTE;}

{TOKEN_GTE} {
    token_stream.emplace_back(TOKEN_GTE, line, col, yytext);
    return TOKEN_GTE;}

{TOKEN_ASSIGN} {
    token_stream.emplace_back(TOKEN_ASSIGN, line, col, yytext);
    return TOKEN_ASSIGN;}

{TOKEN_OR} {
    Token token(TOKEN_DIV, line, col, yytext);
    token_stream.emplace_back(token);
    return TOKEN_OR;}

{TOKEN_VOID} {
    Token token(TOKEN_DIV, line, col, yytext);
    token_stream.emplace_back(token);
    return TOKEN_VOID;}

{TOKEN_CONST} {
    Token token(TOKEN_DIV, line, col, yytext);
    token_stream.emplace_back(token);
    return TOKEN_CONST;}

{TOKEN_RETURN} {
    Token token(TOKEN_DIV, line, col, yytext);
    token_stream.emplace_back(token);
    return TOKEN_RETURN;}

{TOKEN_CONTINUE} {
    Token token(TOKEN_DIV, line, col, yytext);
    token_stream.emplace_back(token);
    return TOKEN_CONTINUE;}

{TOKEN_BREAK} {
    Token token(TOKEN_DIV, line, col, yytext);
    token_stream.emplace_back(token);
    return TOKEN_BREAK;}

{TOKEN_FLOATPOINT} {
    Token token(TOKEN_DIV, line, col, yytext);
    token_stream.emplace_back(token);
    return TOKEN_FLOATPOINT;}

{HEX_CONST} {
    Token token(TOKEN_INTEGER, line, col, (int)(strtol(yytext, NULL, 16)));
    token_stream.emplace_back(token);
    return TOKEN_INTEGER;}

{OCT_CONST} {
    Token token(TOKEN_INTEGER, line, col, (int)(strtol(yytext, NULL, 8)));
    token_stream.emplace_back(token);
    return TOKEN_INTEGER;}

{DEC_CONST} {
    Token token(TOKEN_INTEGER, line, col, (int)(strtol(yytext, NULL, 10)));
    token_stream.emplace_back(token);
    return TOKEN_INTEGER;}

{TOKEN_IDENTIFIER} {
    Token token(TOKEN_IDENTIFIER, line, col, yytext);
    token_stream.emplace_back(token);
    return TOKEN_IDENTIFIER;}

{NEWLINE} { line++;}

%%

vector<Token>& lexical_analysis(const char *input_file){
    if(!(yyin = fopen(input_file,"r"))){
        cout << "[ERROR] No input file\n";
        exit(1);
    }

    while(yylex());
    for (auto & t : token_stream){
		switch (t.type){
			case TOKEN_INTEGER: 
				cout << "Type: " << t.type << " data: " << t.data.int_val << endl;
				break;
			case TOKEN_FLOATPOINT:
				cout << "Type: " << t.type << " data: " << t.data.float_val << endl;
				break;
			case TOKEN_IDENTIFIER:
				cout << "Type: " << t.type << " data: " << t.data.identifier << endl;
				break;
			default:
				cout << "Type: " << t.type << endl;
		}
    }

    return token_stream;
}

int main(int argc, char *argv[]){

    char input_file[256];
	strcpy(input_file, "test.cc");

    if (argc == 2) {
        strcpy(input_file, argv[1]);
    }
    cout << "input_file: " << input_file << endl;
    // yylex()是flex提供的词法分析例程,默认读取stdin
    lexical_analysis(input_file);
    return 0;
}
