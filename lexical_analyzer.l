%option noyywrap
%{
#include <string>
#include "ast.h"
#include "syntax_analyzer.tab.h"

void yyerror(const char *s);
int yycolumn = 1;

#define SAVE_TOKEN     yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t)       yylval.token = t
#define YY_USER_ACTION yylloc.first_line = yylineno;            \
                       yylloc.first_column = yycolumn;          \
                       for (auto i : std::string(yytext_ptr)) { \
                           if (i == '\n') {                     \
                               yylineno++;                      \
                               yycolumn = 1;                    \
                           } else {                             \
                               yycolumn++;                      \
                           }                                    \
                       }                                        
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

DEC_FLOATPOINT ({DIGIT}*[.]{DIGIT}+|{DIGIT}+[.])([eE][+-]?{DIGIT}+)?|{DIGIT}+([eE][+-]?{DIGIT}+)
HEX_FLOATPOINT {HEX_PREFIX}({HEX_DIGIT}*[.]{HEX_DIGIT}+|{HEX_DIGIT}+[.])([pP][+-]?{DIGIT}+)|{HEX_PREFIX}({HEX_DIGIT}+)([pP][+-]?{DIGIT}+)

TOKEN_INTEGER {DEC_INTEGER}|{OCT_INTEGER}|{HEX_INTEGER}
TOKEN_FLOATPOINT  {DEC_FLOATPOINT}|{HEX_FLOATPOINT}

LETTER [a-zA-Z]
TOKEN_IDENTIFIER ({LETTER}|_)({DIGIT}|{LETTER}|_)*

%%

\/\/.*              ;

"/*"                {
                        int c;
                        while((c = yyinput()) != 0) {
                            if(c == '\n') {
                                yylineno++;
                                yycolumn = 1;
                            } else if(c == '*') {
                            if((c = yyinput()) == '/')
                                break;
                            else
                                unput(c);
                            }
                        }
                    }

[\n]                ;
[ ]                 ;
[\t\r]              ;

"+"                 return TOKEN(ADD);
"-"                 return TOKEN(SUB);
"*"                 return TOKEN(MUL);
"/"                 return TOKEN(DIV);
"%"                 return TOKEN(MOD);

"if"                return TOKEN(IF);
"else"              return TOKEN(ELSE);
"while"             return TOKEN(WHILE);
"break"             return TOKEN(BREAK);
"continue"          return TOKEN(CONTINUE);
"return"            return TOKEN(RETURN);

"const"             return TOKEN(CONST);
"int"               return TOKEN(INT);
"void"              return TOKEN(VOID);
"float"             return TOKEN(FLOAT);

{TOKEN_IDENTIFIER}  SAVE_TOKEN; return IDENTIFIER;
{TOKEN_INTEGER}     yylval.token = static_cast<std::int32_t>(strtol(yytext, NULL, 0)); return INTEGER;
{TOKEN_FLOATPOINT}	yylval.f_val = static_cast<float>(strtod(yytext, NULL)); return FLOATPOINT;

"="                 return TOKEN(ASSIGN);
"=="                return TOKEN(EQ);
"!="                return TOKEN(NEQ);

">"                 return TOKEN(GT);
">="                return TOKEN(GTE);
"<"                 return TOKEN(LT);
"<="                return TOKEN(LTE);

"&&"                return TOKEN(AND);
"||"                return TOKEN(OR);
"!"                 return TOKEN(NOT);

"("                 return TOKEN(LEFT_PARENTHESES);
")"                 return TOKEN(RIGHT_PARENTHESES);
"["                 return TOKEN(LEFT_BRACKETS);
"]"                 return TOKEN(RIGHT_BRACKETS);
"{"                 return TOKEN(LEFT_BRACES);
"}"                 return TOKEN(RIGHT_BRACES);

","                 return TOKEN(COMMA);
";"                 return TOKEN(SEMICOLON);

.                   yyerror((std::string("Unknown token: ") + yytext).c_str()); yyterminate();

%%

void scan_string(const char* str)
{
    yy_switch_to_buffer(yy_scan_string(str));
}
