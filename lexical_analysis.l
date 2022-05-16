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

WHITESPACE [ \t\r]+
NEWLINE [\n]

NONZERO_DIGIT [1-9]
DIGIT [0-9]

HEX_PREFIX (0x)|(0X)
HEX_DIGIT [0-9a-fA-F]

OCT_PREFIX 0
OCT_DIGIT [0-7]

DEC_CONST {NONZERO_DIGIT}{DIGIT}*
OCT_CONST {OCT_PREFIX}{OCT_DIGIT}*
HEX_CONST {HEX_PREFIX}{HEX_DIGIT}*

DEC_FLOATPOINT ({DIGIT}*[.]{DIGIT}+|{DIGIT}+[.])([eE][+-]?{DIGIT}+)?|{DIGIT}+([eE][+-]?{DIGIT}+)
HEX_FLOATPOINT {HEX_PREFIX}({HEX_DIGIT}*[.]{HEX_DIGIT}+|{HEX_DIGIT}+[.])([pP][+-]?{DIGIT}+)|{HEX_PREFIX}({HEX_DIGIT}+)([pP][+-]?{DIGIT}+)
TOKEN_FLOATPOINT  {DEC_FLOATPOINT}|{HEX_FLOATPOINT}

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
	SAVE_TOKEN(TOKEN(TOKEN_ADD, yytext));

    return TOKEN_ADD;}

{TOKEN_SUB} {
	SAVE_TOKEN(TOKEN(TOKEN_SUB, yytext));
    return TOKEN_SUB;}

{TOKEN_MUL} {
	SAVE_TOKEN(TOKEN(TOKEN_MUL, yytext));

    return TOKEN_MUL;}

{TOKEN_DIV} {
    SAVE_TOKEN(TOKEN(TOKEN_DIV, yytext));

    return TOKEN_DIV;}

{TOKEN_MOD} {
    SAVE_TOKEN(TOKEN(TOKEN_MOD, yytext));

    return TOKEN_MOD;}

{TOKEN_EQ} {
    token_stream.emplace_back(TOKEN_EQ, line, COL(yytext));

    return TOKEN_EQ;}

{TOKEN_NEQ} {
    SAVE_TOKEN(TOKEN(TOKEN_NEQ, yytext));

    return TOKEN_NEQ;}

{TOKEN_LT} {
    SAVE_TOKEN(TOKEN(TOKEN_LT, yytext));

    return TOKEN_LT;}

{TOKEN_GT} {
    SAVE_TOKEN(TOKEN(TOKEN_GT, yytext));

    return TOKEN_GT;}

{TOKEN_LTE} {
    SAVE_TOKEN(TOKEN(TOKEN_LTE, yytext));

    return TOKEN_LTE;}

{TOKEN_GTE} {
    SAVE_TOKEN(TOKEN(TOKEN_GTE, yytext));

    return TOKEN_GTE;}

{TOKEN_ASSIGN} {
    SAVE_TOKEN(TOKEN(TOKEN_ASSIGN, yytext));

    return TOKEN_ASSIGN;}

{TOKEN_NOT} {
    SAVE_TOKEN(TOKEN(TOKEN_NOT, yytext));

    return TOKEN_NOT;}

{TOKEN_AND} {
    SAVE_TOKEN(TOKEN(TOKEN_AND, yytext));

    return TOKEN_AND;}

{TOKEN_OR} {
    SAVE_TOKEN(TOKEN(TOKEN_OR, yytext));

    return TOKEN_OR;}


{TOKEN_IF} {
    SAVE_TOKEN(TOKEN(TOKEN_IF, yytext));

    return TOKEN_IF;}

{TOKEN_ELSE} {
    SAVE_TOKEN(TOKEN(TOKEN_ELSE, yytext));

    return TOKEN_ELSE;}

{TOKEN_WHILE} {
    SAVE_TOKEN(TOKEN(TOKEN_WHILE, yytext));

    return TOKEN_WHILE;}

{TOKEN_INT} {
    SAVE_TOKEN(TOKEN(TOKEN_INT, yytext));

    return TOKEN_INT;}

{TOKEN_FLOAT} {
    SAVE_TOKEN(TOKEN(TOKEN_FLOAT, yytext));

    return TOKEN_FLOAT;}

{TOKEN_VOID} {
    SAVE_TOKEN(TOKEN(TOKEN_VOID, yytext));

    return TOKEN_VOID;}

{TOKEN_CONST} {
    SAVE_TOKEN(TOKEN(TOKEN_CONST, yytext));

    return TOKEN_CONST;}

{TOKEN_RETURN} {
    SAVE_TOKEN(TOKEN(TOKEN_RETURN, yytext));

    return TOKEN_RETURN;}

{TOKEN_CONTINUE} {
    SAVE_TOKEN(TOKEN(TOKEN_CONTINUE, yytext));

    return TOKEN_CONTINUE;}

{TOKEN_BREAK} {
    SAVE_TOKEN(TOKEN(TOKEN_BREAK, yytext));

    return TOKEN_BREAK;}

{TOKEN_SEMICOLON} {
    SAVE_TOKEN(TOKEN(TOKEN_SEMICOLON, yytext));

    return TOKEN_SEMICOLON;}

{TOKEN_COMMA} {
    SAVE_TOKEN(TOKEN(TOKEN_COMMA, yytext));

    return TOKEN_COMMA;}

{TOKEN_LEFT_PARENTHESES} {
    SAVE_TOKEN(TOKEN(TOKEN_LEFT_PARENTHESES, yytext));

    return TOKEN_LEFT_PARENTHESES;}

{TOKEN_RIGHT_PARENTHESES} {
    SAVE_TOKEN(TOKEN(TOKEN_RIGHT_PARENTHESES, yytext));

    return TOKEN_RIGHT_PARENTHESES;}

{TOKEN_LEFT_BRACES} {
    SAVE_TOKEN(TOKEN(TOKEN_LEFT_BRACES, yytext));

    return TOKEN_LEFT_BRACES;}

{TOKEN_RIGHT_BRACES} {
    SAVE_TOKEN(TOKEN(TOKEN_RIGHT_BRACES, yytext));

    return TOKEN_RIGHT_BRACES;}

{TOKEN_LEFT_BRACKETS} {
    SAVE_TOKEN(TOKEN(TOKEN_LEFT_BRACKETS, yytext));

    return TOKEN_LEFT_BRACKETS;}

{TOKEN_RIGHT_BRACKETS} {
    SAVE_TOKEN(TOKEN(TOKEN_RIGHT_BRACKETS, yytext));

    return TOKEN_RIGHT_BRACKETS;}

{TOKEN_IDENTIFIER} {
    Token token(TOKEN_IDENTIFIER, line, COL(yytext), yytext);
    SAVE_TOKEN(token);

    return TOKEN_IDENTIFIER;}

{TOKEN_FLOATPOINT} {
    Token token(TOKEN_FLOATPOINT, line, COL(yytext),  static_cast<float>(strtod(yytext,NULL)));
    SAVE_TOKEN(token);

    return TOKEN_FLOATPOINT;}

{HEX_CONST} {
    Token token(TOKEN_INTEGER, line, COL(yytext), static_cast<int>(strtol(yytext, NULL, 16)));
    SAVE_TOKEN(token);

    return TOKEN_INTEGER;}

{OCT_CONST} {
    Token token(TOKEN_INTEGER, line, COL(yytext), static_cast<int>(strtol(yytext, NULL, 8)));
    SAVE_TOKEN(token);

    return TOKEN_INTEGER;}

{DEC_CONST} {
    Token token(TOKEN_INTEGER, line, COL(yytext), static_cast<int>(strtol(yytext, NULL, 10)));
    SAVE_TOKEN(token);

    return TOKEN_INTEGER;}

{NEWLINE} ;
{WHITESPACE} ;

. {printf("other token: %s\n", yytext);}

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
