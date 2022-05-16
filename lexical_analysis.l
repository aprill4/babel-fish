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

#define YY_USER_ACTION for (auto i: string(yytext_ptr)) { \
					       if (i == '\n') { \
						       line++;     \
							   col = 1;    \
						   } else {        \
								col++;     \
						   }               \
					   }                   

#define COL(yytext) col - strlen(yytext)

#define TOKEN(type, yytext) Token(type, line, COL(yytext))

#define SAVE_TOKEN(token) token_stream.emplace_back(token)

%}

NONZERO_DIGIT [1-9]
DIGIT [0-9]

HEX_PREFIX (0x)|(0X)
HEX_DIGIT [0-9a-fA-Z]

OCT_PREFIX 0
OCT_DIGIT [0-7]

DEC_CONST {NONZERO_DIGIT}{DIGIT}*
OCT_CONST {OCT_PREFIX}{OCT_DIGIT}*
HEX_CONST {HEX_PREFIX}{HEX_DIGIT}*

DEC_FLOATPOINT ({DIGIT}*.{DIGIT}+|{DIGIT}+.)([eE][+-]?{DIGIT}+)?|{DIGIT}+([eE][+-]?{DIGIT}+)
HEX_FLOATPOINT {HEX_PREFIX}({HEX_DIGIT}*.{HEX_DIGIT}+|{HEX_DIGIT}+.)([pP][+-]?{DIGIT}+)|{HEX_PREFIX}({HEX_DIGIT}+)([pP][+-]?{DIGIT}+)
TOKEN_FLOATPOINT  {DEC_FLOATPOINT}|{HEX_FLOATPOINT}

LETTER [a-zA-Z]
TOKEN_IDENTIFIER ({LETTER}|_)({DIGIT}|{LETTER}|_)*

COMMENT ("//")(.)*
MULTILINE_COMMENT "/*"

%%
\/\/.*				;

"/*" 				{
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
						}
					}

[\n] 				;
[  ] 				;
[\t\r]				;

"+" 				SAVE_TOKEN(TOKEN(TOKEN_ADD, yytext)); return TOKEN_ADD;
"-" 				SAVE_TOKEN(TOKEN(TOKEN_SUB, yytext)); return TOKEN_SUB;
"*" 				SAVE_TOKEN(TOKEN(TOKEN_MUL, yytext)); return TOKEN_MUL;
"/" 				SAVE_TOKEN(TOKEN(TOKEN_DIV, yytext)); return TOKEN_DIV;
"%" 				SAVE_TOKEN(TOKEN(TOKEN_MOD, yytext)); return TOKEN_MOD;

"=="				SAVE_TOKEN(TOKEN(TOKEN_EQ, yytext)); return TOKEN_EQ;
"!=" 				SAVE_TOKEN(TOKEN(TOKEN_NEQ, yytext)); return TOKEN_NEQ;

"<" 				SAVE_TOKEN(TOKEN(TOKEN_LT, yytext)); return TOKEN_LT;
">"					SAVE_TOKEN(TOKEN(TOKEN_GT, yytext)); return TOKEN_GT;
"<="				SAVE_TOKEN(TOKEN(TOKEN_LTE, yytext)); return TOKEN_LTE;
">="				SAVE_TOKEN(TOKEN(TOKEN_GTE, yytext)); return TOKEN_GTE;

"="					SAVE_TOKEN(TOKEN(TOKEN_ASSIGN, yytext)); return TOKEN_ASSIGN;
"!"					SAVE_TOKEN(TOKEN(TOKEN_NOT, yytext)); return TOKEN_NOT;

"&&"				SAVE_TOKEN(TOKEN(TOKEN_AND, yytext)); return TOKEN_AND;
"||"				SAVE_TOKEN(TOKEN(TOKEN_OR, yytext)); return TOKEN_OR;

"if"				SAVE_TOKEN(TOKEN(TOKEN_IF, yytext)); return TOKEN_IF;
"else"				SAVE_TOKEN(TOKEN(TOKEN_ELSE, yytext)); return TOKEN_ELSE;
"while"				SAVE_TOKEN(TOKEN(TOKEN_WHILE, yytext)); return TOKEN_WHILE;
"continue"			SAVE_TOKEN(TOKEN(TOKEN_CONTINUE, yytext)); return TOKEN_CONTINUE;
"break"				SAVE_TOKEN(TOKEN(TOKEN_BREAK, yytext)); return TOKEN_BREAK;

"int"				SAVE_TOKEN(TOKEN(TOKEN_INT, yytext)); return TOKEN_INT;
"float"				SAVE_TOKEN(TOKEN(TOKEN_FLOAT, yytext)); return TOKEN_FLOAT;
"void"				SAVE_TOKEN(TOKEN(TOKEN_VOID, yytext)); return TOKEN_VOID;
"const"				SAVE_TOKEN(TOKEN(TOKEN_CONST, yytext)); return TOKEN_CONST;
"return"			SAVE_TOKEN(TOKEN(TOKEN_RETURN, yytext)); return TOKEN_RETURN;

";"					SAVE_TOKEN(TOKEN(TOKEN_SEMICOLON, yytext)); return TOKEN_SEMICOLON;
","					SAVE_TOKEN(TOKEN(TOKEN_COMMA, yytext)); return TOKEN_COMMA;
"("					SAVE_TOKEN(TOKEN(TOKEN_LEFT_PARENTHESES, yytext)); return TOKEN_LEFT_PARENTHESES;
")"					SAVE_TOKEN(TOKEN(TOKEN_RIGHT_PARENTHESES, yytext)); return TOKEN_RIGHT_PARENTHESES;
"{"					SAVE_TOKEN(TOKEN(TOKEN_LEFT_BRACES, yytext)); return TOKEN_LEFT_BRACES;
"}"					SAVE_TOKEN(TOKEN(TOKEN_RIGHT_BRACES, yytext)); return TOKEN_RIGHT_BRACES;
"["					SAVE_TOKEN(TOKEN(TOKEN_LEFT_BRACKETS, yytext)); return TOKEN_LEFT_BRACKETS;
"]"					SAVE_TOKEN(TOKEN(TOKEN_RIGHT_BRACKETS, yytext)); return TOKEN_RIGHT_BRACKETS;

{TOKEN_IDENTIFIER}	{Token token(TOKEN_IDENTIFIER, line, COL(yytext), yytext); SAVE_TOKEN(token); return TOKEN_IDENTIFIER;}

{TOKEN_FLOATPOINT}	{Token token(TOKEN_FLOATPOINT, line, COL(yytext), static_cast<float>(strtod(yytext,NULL))); SAVE_TOKEN(token); return TOKEN_FLOATPOINT;}

{HEX_CONST} 		{Token token(TOKEN_INTEGER, line, COL(yytext), static_cast<int>(strtol(yytext, NULL, 16))); SAVE_TOKEN(token); return TOKEN_INTEGER;}

{OCT_CONST} 		{Token token(TOKEN_INTEGER, line, COL(yytext), static_cast<int>(strtol(yytext, NULL, 8))); SAVE_TOKEN(token); return TOKEN_INTEGER;}

{DEC_CONST} 		{Token token(TOKEN_INTEGER, line, COL(yytext), static_cast<int>(strtol(yytext, NULL, 10))); SAVE_TOKEN(token); return TOKEN_INTEGER;}

. 					printf("other token: %s\n", yytext);

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
