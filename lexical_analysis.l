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

TOKEN_ADD \+
TOKEN_SUB -
TOKEN_MUL \*
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
TOKEN_AND \&\&
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
TOKEN_LEFT_PARENTHESES \(
TOKEN_RIGHT_PARENTHESES \)
TOKEN_LEFT_BRACKETS \[
TOKEN_RIGHT_BRACKETS \]
TOKEN_LEFT_BRACES \{
TOKEN_RIGHT_BRACES \}

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
TOKEN_IDENTIFIER ({LETTER}|_)({DIGIT}|{LETTER}|_)*

COMMENT ("//")(.)*
MULTILINE_COMMENT "/*"

%%
{COMMENT} ;

{MULTILINE_COMMENT} {
	int c;
	while ((c = yyinput()) != 0){
		if (c == '\n'){
			line++;
			col = 1;
		} else if(c == '*') {
			if ((c = yyinput()) == '/')
				break;
			else {
				unput(c);
			}
		}
	}}

{TOKEN_ADD} {
    token_stream.emplace_back(TOKEN_ADD, line, col);

	col += strlen(yytext);
    return TOKEN_ADD;}

{TOKEN_SUB} {
    token_stream.emplace_back(TOKEN_SUB, line, col);

	col += strlen(yytext);
    return TOKEN_SUB;}

{TOKEN_MUL} {
    token_stream.emplace_back(TOKEN_MUL, line, col);

	col += strlen(yytext);
    return TOKEN_MUL;}

{TOKEN_DIV} {
    token_stream.emplace_back(TOKEN_DIV, line, col);

	col += strlen(yytext);
    return TOKEN_DIV;}

{TOKEN_MOD} {
    token_stream.emplace_back(TOKEN_MOD, line, col);

	col += strlen(yytext);
    return TOKEN_MOD;}

{TOKEN_EQ} {
    token_stream.emplace_back(TOKEN_EQ, line, col);

	col += strlen(yytext);
    return TOKEN_EQ;}

{TOKEN_NEQ} {
    token_stream.emplace_back(TOKEN_NEQ, line, col);

	col += strlen(yytext);
    return TOKEN_NEQ;}

{TOKEN_LT} {
    token_stream.emplace_back(TOKEN_LT, line, col);

	col += strlen(yytext);
    return TOKEN_LT;}

{TOKEN_GT} {
    token_stream.emplace_back(TOKEN_GT, line, col);

	col += strlen(yytext);
    return TOKEN_GT;}

{TOKEN_LTE} {
    token_stream.emplace_back(TOKEN_LTE, line, col);

	col += strlen(yytext);
    return TOKEN_LTE;}

{TOKEN_GTE} {
    token_stream.emplace_back(TOKEN_GTE, line, col);

	col += strlen(yytext);
    return TOKEN_GTE;}

{TOKEN_ASSIGN} {
    token_stream.emplace_back(TOKEN_ASSIGN, line, col);

	col += strlen(yytext);
    return TOKEN_ASSIGN;}

{TOKEN_NOT} {
    token_stream.emplace_back(TOKEN_NOT, line, col);

	col += strlen(yytext);
    return TOKEN_NOT;}

{TOKEN_AND} {
    token_stream.emplace_back(TOKEN_AND, line, col);

	col += strlen(yytext);
    return TOKEN_AND;}

{TOKEN_OR} {
    token_stream.emplace_back(TOKEN_OR, line, col);

	col += strlen(yytext);
    return TOKEN_OR;}


{TOKEN_IF} {
    token_stream.emplace_back(TOKEN_IF, line, col);

	col += strlen(yytext);
    return TOKEN_IF;}

{TOKEN_ELSE} {
    token_stream.emplace_back(TOKEN_ELSE, line, col);

	col += strlen(yytext);
    return TOKEN_ELSE;}

{TOKEN_WHILE} {
    token_stream.emplace_back(TOKEN_WHILE, line, col);

	col += strlen(yytext);
    return TOKEN_WHILE;}

{TOKEN_INT} {
    token_stream.emplace_back(TOKEN_INT, line, col);

	col += strlen(yytext);
    return TOKEN_INT;}

{TOKEN_FLOAT} {
    token_stream.emplace_back(TOKEN_FLOAT, line, col);

	col += strlen(yytext);
    return TOKEN_FLOAT;}

{TOKEN_VOID} {
    token_stream.emplace_back(TOKEN_VOID, line, col);

	col += strlen(yytext);
    return TOKEN_VOID;}

{TOKEN_CONST} {
    token_stream.emplace_back(TOKEN_CONST, line, col);

	col += strlen(yytext);
    return TOKEN_CONST;}

{TOKEN_RETURN} {
    token_stream.emplace_back(TOKEN_RETURN, line, col);

	col += strlen(yytext);
    return TOKEN_RETURN;}

{TOKEN_CONTINUE} {
    token_stream.emplace_back(TOKEN_CONTINUE, line, col);

	col += strlen(yytext);
    return TOKEN_CONTINUE;}

{TOKEN_BREAK} {
    token_stream.emplace_back(TOKEN_BREAK, line, col);

	col += strlen(yytext);
    return TOKEN_BREAK;}

{TOKEN_SEMICOLON} {
    token_stream.emplace_back(TOKEN_SEMICOLON, line, col);

	col += strlen(yytext);
    return TOKEN_SEMICOLON;}

{TOKEN_COMMA} {
    token_stream.emplace_back(TOKEN_COMMA, line, col);

	col += strlen(yytext);
    return TOKEN_COMMA;}

{TOKEN_LEFT_PARENTHESES} {
    token_stream.emplace_back(TOKEN_LEFT_PARENTHESES, line, col);

	col += strlen(yytext);
    return TOKEN_LEFT_PARENTHESES;}

{TOKEN_RIGHT_PARENTHESES} {
    token_stream.emplace_back(TOKEN_RIGHT_PARENTHESES, line, col);

	col += strlen(yytext);
    return TOKEN_RIGHT_PARENTHESES;}

{TOKEN_LEFT_BRACES} {
    token_stream.emplace_back(TOKEN_LEFT_BRACES, line, col);

	col += strlen(yytext);
    return TOKEN_LEFT_BRACES;}

{TOKEN_RIGHT_BRACES} {
    token_stream.emplace_back(TOKEN_RIGHT_BRACES, line, col);

	col += strlen(yytext);
    return TOKEN_RIGHT_BRACES;}

{TOKEN_LEFT_BRACKETS} {
    token_stream.emplace_back(TOKEN_LEFT_BRACKETS, line, col);

	col += strlen(yytext);
    return TOKEN_LEFT_BRACKETS;}

{TOKEN_RIGHT_BRACKETS} {
    token_stream.emplace_back(TOKEN_RIGHT_BRACKETS, line, col);

	col += strlen(yytext);
    return TOKEN_RIGHT_BRACKETS;}

{TOKEN_IDENTIFIER} {
    Token token(TOKEN_IDENTIFIER, line, col, yytext);
    token_stream.emplace_back(token);

	col += strlen(yytext);
    return TOKEN_IDENTIFIER;}

{TOKEN_FLOATPOINT} {
    Token token(TOKEN_DIV, line, col, yytext);
    token_stream.emplace_back(token);

	col += strlen(yytext);
    return TOKEN_FLOATPOINT;}

{HEX_CONST} {
    Token token(TOKEN_INTEGER, line, col, (int)(strtol(yytext, NULL, 16)));
    token_stream.emplace_back(token);

	col += strlen(yytext);
    return TOKEN_INTEGER;}

{OCT_CONST} {
    Token token(TOKEN_INTEGER, line, col, (int)(strtol(yytext, NULL, 8)));
    token_stream.emplace_back(token);

	col += strlen(yytext);
    return TOKEN_INTEGER;}

{DEC_CONST} {
    Token token(TOKEN_INTEGER, line, col, (int)(strtol(yytext, NULL, 10)));
    token_stream.emplace_back(token);

	col += strlen(yytext);
    return TOKEN_INTEGER;}

{NEWLINE} { line++; col = 1;}
{SPACE} {col++;}
{TAB} {col++;}

%%

vector<Token>& lexical_analysis(const char *input_file){
    if(!(yyin = fopen(input_file,"r"))){
        cout << "[ERROR] No input file\n";
        exit(1);
    }

    while(yylex());
    for (auto & t : token_stream){
		cout << "line " << t.line << ", col " << t.col;
		cout << ", "<< lookup[t.type];
		switch (t.type){
			case TOKEN_INTEGER: 
				cout << ", " << t.data.int_val << endl;
				break;
			case TOKEN_FLOATPOINT:
				cout << ", " << t.data.float_val << endl;
				break;
			case TOKEN_IDENTIFIER:
				cout << ", " << t.data.identifier << endl;
				break;
			default:
				cout << endl;
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
