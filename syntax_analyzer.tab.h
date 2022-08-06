/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_SYNTAX_ANALYZER_TAB_H_INCLUDED
# define YY_YY_SYNTAX_ANALYZER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ADD = 258,
    SUB = 259,
    MUL = 260,
    DIV = 261,
    MOD = 262,
    ASSIGN = 263,
    EQ = 264,
    NEQ = 265,
    LT = 266,
    LTE = 267,
    GT = 268,
    GTE = 269,
    AND = 270,
    OR = 271,
    NOT = 272,
    IF = 273,
    ELSE = 274,
    WHILE = 275,
    BREAK = 276,
    CONTINUE = 277,
    RETURN = 278,
    CONST = 279,
    INT = 280,
    VOID = 281,
    FLOAT = 282,
    LEFT_PARENTHESES = 283,
    RIGHT_PARENTHESES = 284,
    LEFT_BRACKETS = 285,
    RIGHT_BRACKETS = 286,
    LEFT_BRACES = 287,
    RIGHT_BRACES = 288,
    COMMA = 289,
    SEMICOLON = 290,
    IDENTIFIER = 291,
    INTEGER = 292,
    FLOATPOINT = 293
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "syntax_analyzer.y"

      SysType type;
      std::string *string;
      std::int32_t token;
      float f_val;
      Root* root;
      DeclareStatement* declare_statement;
      FunctionDefinition* function_definition;
      Identifier* ident;
      Declare* declare;
      Expression* expr;
      Block* block;
      Statement* stmt;
      ArrayValue* array_val;
      FormalArgumentList* formal_args;
      FormalArgument* formal_arg;
      ActualArgumentList* actual_args;

#line 115 "syntax_analyzer.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SYNTAX_ANALYZER_TAB_H_INCLUDED  */
