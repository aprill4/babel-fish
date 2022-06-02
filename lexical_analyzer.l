%option noyywrap
%{
#include "token.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <cstdlib>
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

#define COL col - strlen(yytext)

#define SAVE_TOKEN(type)	token_stream.emplace_back(type, line, COL); \
							return type

#define SAVE_VAL(type)	token_stream.emplace_back(token)

%}

NONZERO_DIGIT [1-9]
DIGIT [0-9]

HEX_PREFIX (0x)|(0X)
HEX_DIGIT [0-9a-fA-F]

OCT_PREFIX 0
OCT_DIGIT [0-7]

DEC_INTEGER {NONZERO_DIGIT}{DIGIT}*
OCT_INTEGER {OCT_PREFIX}{OCT_DIGIT}*
HEX_INTEGER {HEX_PREFIX}{HEX_DIGIT}*

TOKEN_INTEGER {DEC_INTEGER}|{OCT_INTEGER}|{HEX_INTEGER}

DEC_FLOATPOINT ({DIGIT}*[.]{DIGIT}+|{DIGIT}+[.])([eE][+-]?{DIGIT}+)?|{DIGIT}+([eE][+-]?{DIGIT}+)
HEX_FLOATPOINT {HEX_PREFIX}({HEX_DIGIT}*[.]{HEX_DIGIT}+|{HEX_DIGIT}+[.])([pP][+-]?{DIGIT}+)|{HEX_PREFIX}({HEX_DIGIT}+)([pP][+-]?{DIGIT}+)

TOKEN_FLOATPOINT  {DEC_FLOATPOINT}|{HEX_FLOATPOINT}

LETTER [a-zA-Z]
TOKEN_IDENTIFIER ({LETTER}|_)({DIGIT}|{LETTER}|_)*

COMMENT ("//")(.)*
MULTILINE_COMMENT \/\*

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

"+" 				SAVE_TOKEN(TOKEN_ADD); 
"-" 				SAVE_TOKEN(TOKEN_SUB); 
"*" 				SAVE_TOKEN(TOKEN_MUL); 
"/" 				SAVE_TOKEN(TOKEN_DIV); 
"%" 				SAVE_TOKEN(TOKEN_MOD); 

"=="				SAVE_TOKEN(TOKEN_EQ); 
"!=" 				SAVE_TOKEN(TOKEN_NEQ); 

"<" 				SAVE_TOKEN(TOKEN_LT); 
">"					SAVE_TOKEN(TOKEN_GT); 
"<="				SAVE_TOKEN(TOKEN_LTE); 
">="				SAVE_TOKEN(TOKEN_GTE); 

"="					SAVE_TOKEN(TOKEN_ASSIGN); 
"!"					SAVE_TOKEN(TOKEN_NOT); 

"&&"				SAVE_TOKEN(TOKEN_AND); 
"||"				SAVE_TOKEN(TOKEN_OR); 

"if"				SAVE_TOKEN(TOKEN_IF); 
"else"				SAVE_TOKEN(TOKEN_ELSE); 
"while"				SAVE_TOKEN(TOKEN_WHILE); 
"continue"			SAVE_TOKEN(TOKEN_CONTINUE); 
"break"				SAVE_TOKEN(TOKEN_BREAK); 

"int"				SAVE_TOKEN(TOKEN_INT); 
"float"				SAVE_TOKEN(TOKEN_FLOAT); 
"void"				SAVE_TOKEN(TOKEN_VOID); 
"const"				SAVE_TOKEN(TOKEN_CONST); 
"return"			SAVE_TOKEN(TOKEN_RETURN); 

";"					SAVE_TOKEN(TOKEN_SEMICOLON); 
","					SAVE_TOKEN(TOKEN_COMMA); 
"("					SAVE_TOKEN(TOKEN_LEFT_PARENTHESES); 
")"					SAVE_TOKEN(TOKEN_RIGHT_PARENTHESES); 
"{"					SAVE_TOKEN(TOKEN_LEFT_BRACES); 
"}"					SAVE_TOKEN(TOKEN_RIGHT_BRACES); 
"["					SAVE_TOKEN(TOKEN_LEFT_BRACKETS); 
"]"					SAVE_TOKEN(TOKEN_RIGHT_BRACKETS); 

{TOKEN_IDENTIFIER}	{Token token(TOKEN_IDENTIFIER, line, COL, yytext); SAVE_VAL(token); return TOKEN_IDENTIFIER;}

{TOKEN_FLOATPOINT}	{Token token(TOKEN_FLOATPOINT, line, COL, static_cast<float>(strtod(yytext, NULL))); SAVE_VAL(token); return TOKEN_FLOATPOINT;}

{TOKEN_INTEGER}  	{Token token(TOKEN_INTEGER, line, COL, static_cast<int>(strtol(yytext, NULL, 0))); SAVE_VAL(token); return TOKEN_INTEGER;}

. 					printf("unrecognized token: %s\n", yytext);

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
