/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
/* Tokens.  */
#define ADD 258
#define SUB 259
#define MUL 260
#define DIV 261
#define MOD 262
#define ASSIGN 263
#define EQ 264
#define NEQ 265
#define LT 266
#define LTE 267
#define GT 268
#define GTE 269
#define AND 270
#define OR 271
#define NOT 272
#define IF 273
#define ELSE 274
#define WHILE 275
#define BREAK 276
#define CONTINUE 277
#define RETURN 278
#define CONST 279
#define INT 280
#define VOID 281
#define FLOAT 282
#define LEFT_PARENTHESES 283
#define RIGHT_PARENTHESES 284
#define LEFT_BRACKETS 285
#define RIGHT_BRACKETS 286
#define LEFT_BRACES 287
#define RIGHT_BRACES 288
#define COMMA 289
#define SEMICOLON 290
#define IDENTIFIER 291
#define INTEGER 292
#define FLOATPOINT 293




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 19 "syntax_analyzer.y"
{
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
}
/* Line 1529 of yacc.c.  */
#line 144 "syntax_analyzer.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
