/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



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




/* Copy the first part of user declarations.  */
#line 1 "syntax_analyzer.y"

#include <iostream>
#include <cstdlib>
#include "ast.h"
#include "syntax_analyzer.tab.h"
Root* root = nullptr;

extern int yylex();

void yyerror(const char *s) {
      using namespace std;
      cerr << yylloc.first_line << ':' << yylloc.first_column << ": error: " << s << endl;
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 207 "syntax_analyzer.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 232 "syntax_analyzer.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   279

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNRULES -- Number of states.  */
#define YYNSTATES  182

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    11,    13,    16,    19,    21,
      23,    29,    35,    41,    47,    50,    55,    58,    63,    67,
      73,    77,    83,    88,    93,    96,   100,   102,   104,   108,
     112,   114,   116,   118,   120,   122,   127,   132,   136,   138,
     140,   142,   146,   148,   152,   154,   158,   162,   164,   168,
     172,   176,   180,   182,   186,   190,   192,   196,   200,   204,
     206,   210,   215,   218,   221,   224,   230,   237,   243,   250,
     252,   256,   259,   261,   266,   271,   273,   277,   280,   284,
     286,   289,   291,   293,   298,   300,   303,   305,   311,   319,
     325,   328,   331,   334
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      40,     0,    -1,    40,    41,    -1,    40,    60,    -1,    41,
      -1,    60,    -1,    43,    35,    -1,    44,    35,    -1,    25,
      -1,    27,    -1,    24,    42,    49,     8,    57,    -1,    43,
      34,    49,     8,    57,    -1,    24,    42,    45,     8,    46,
      -1,    43,    34,    45,     8,    46,    -1,    42,    49,    -1,
      42,    49,     8,    57,    -1,    42,    45,    -1,    42,    45,
       8,    46,    -1,    44,    34,    49,    -1,    44,    34,    49,
       8,    57,    -1,    44,    34,    45,    -1,    44,    34,    45,
       8,    46,    -1,    49,    30,    57,    31,    -1,    45,    30,
      57,    31,    -1,    32,    33,    -1,    32,    47,    33,    -1,
      57,    -1,    46,    -1,    47,    34,    57,    -1,    47,    34,
      46,    -1,    37,    -1,    38,    -1,    36,    -1,    49,    -1,
      51,    -1,    49,    30,    57,    31,    -1,    51,    30,    57,
      31,    -1,    28,    57,    29,    -1,    50,    -1,    48,    -1,
      54,    -1,    53,    16,    54,    -1,    55,    -1,    54,    15,
      55,    -1,    56,    -1,    55,     9,    56,    -1,    55,    10,
      56,    -1,    57,    -1,    56,    13,    57,    -1,    56,    14,
      57,    -1,    56,    11,    57,    -1,    56,    12,    57,    -1,
      58,    -1,    57,     3,    58,    -1,    57,     4,    58,    -1,
      59,    -1,    58,     5,    59,    -1,    58,     6,    59,    -1,
      58,     7,    59,    -1,    52,    -1,    49,    28,    29,    -1,
      49,    28,    64,    29,    -1,     3,    59,    -1,     4,    59,
      -1,    17,    59,    -1,    42,    49,    28,    29,    65,    -1,
      42,    49,    28,    61,    29,    65,    -1,    26,    49,    28,
      29,    65,    -1,    26,    49,    28,    61,    29,    65,    -1,
      62,    -1,    61,    34,    62,    -1,    42,    49,    -1,    63,
      -1,    42,    49,    30,    31,    -1,    63,    30,    57,    31,
      -1,    57,    -1,    64,    34,    57,    -1,    32,    33,    -1,
      32,    66,    33,    -1,    67,    -1,    66,    67,    -1,    41,
      -1,    68,    -1,    50,     8,    57,    35,    -1,    35,    -1,
      57,    35,    -1,    65,    -1,    18,    28,    53,    29,    68,
      -1,    18,    28,    53,    29,    68,    19,    68,    -1,    20,
      28,    53,    29,    68,    -1,    21,    35,    -1,    22,    35,
      -1,    23,    35,    -1,    23,    57,    35,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    68,    68,    73,    80,    86,    96,    97,   100,   101,
     104,   108,   112,   116,   122,   126,   130,   134,   138,   142,
     146,   150,   156,   157,   160,   161,   163,   167,   171,   175,
     180,   181,   184,   187,   188,   191,   195,   201,   202,   203,
     206,   207,   210,   211,   214,   215,   216,   219,   220,   221,
     222,   223,   226,   227,   228,   231,   232,   233,   234,   237,
     238,   241,   244,   245,   246,   249,   252,   255,   258,   263,
     267,   273,   274,   277,   281,   287,   288,   291,   294,   314,
     318,   324,   325,   328,   329,   330,   331,   332,   341,   356,
     365,   366,   367,   368
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ADD", "SUB", "MUL", "DIV", "MOD",
  "ASSIGN", "EQ", "NEQ", "LT", "LTE", "GT", "GTE", "AND", "OR", "NOT",
  "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", "RETURN", "CONST", "INT",
  "VOID", "FLOAT", "LEFT_PARENTHESES", "RIGHT_PARENTHESES",
  "LEFT_BRACKETS", "RIGHT_BRACKETS", "LEFT_BRACES", "RIGHT_BRACES",
  "COMMA", "SEMICOLON", "IDENTIFIER", "INTEGER", "FLOATPOINT", "$accept",
  "CompUnit", "Decl", "BType", "ConstDecl", "VarDecl", "ArrayIdent",
  "ArrayVal", "ArrayVals", "Number", "Ident", "LVal", "ArrayItem",
  "PrimaryExp", "LOrExp", "LAndExp", "EqExp", "RelExp", "AddExp", "MulExp",
  "UnaryExp", "FuncDef", "FuncFParams", "FuncFParam", "FuncFParamArray",
  "FuncRParams", "Block", "BlockItems", "BlockItem", "Stmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    40,    40,    40,    41,    41,    42,    42,
      43,    43,    43,    43,    44,    44,    44,    44,    44,    44,
      44,    44,    45,    45,    46,    46,    47,    47,    47,    47,
      48,    48,    49,    50,    50,    51,    51,    52,    52,    52,
      53,    53,    54,    54,    55,    55,    55,    56,    56,    56,
      56,    56,    57,    57,    57,    58,    58,    58,    58,    59,
      59,    59,    59,    59,    59,    60,    60,    60,    60,    61,
      61,    62,    62,    63,    63,    64,    64,    65,    65,    66,
      66,    67,    67,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     2,     2,     1,     1,
       5,     5,     5,     5,     2,     4,     2,     4,     3,     5,
       3,     5,     4,     4,     2,     3,     1,     1,     3,     3,
       1,     1,     1,     1,     1,     4,     4,     3,     1,     1,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       3,     4,     2,     2,     2,     5,     6,     5,     6,     1,
       3,     2,     1,     4,     4,     1,     3,     2,     3,     1,
       2,     1,     1,     4,     1,     2,     1,     5,     7,     5,
       2,     2,     2,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     8,     0,     9,     0,     4,     0,     0,     0,
       5,     0,    32,     0,     1,     2,     3,    16,    14,     0,
       6,     0,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    20,    18,     0,     0,     0,     0,     0,
      69,    72,     0,    17,     0,     0,     0,     0,    30,    31,
      39,    33,    38,    34,    59,     0,    52,    55,    15,     0,
       0,     0,     0,     0,     0,     0,    12,    10,     0,    67,
      71,     0,     0,     0,    24,    27,     0,    26,    62,    63,
      64,     0,     0,     0,     0,     0,     0,    23,     0,     0,
       0,    65,     0,    22,    13,    11,    21,    19,     0,     0,
       0,     0,     0,    77,    84,    81,     0,    38,     0,    86,
       0,    79,    82,     0,    68,    70,     0,    25,     0,    37,
      60,    75,     0,     0,     0,    53,    54,    56,    57,    58,
      66,     0,     0,    90,    91,    92,     0,    14,     0,    85,
      78,    80,    73,    74,    29,    28,    61,     0,    35,    36,
       0,    40,    42,    44,    47,     0,    93,     0,    76,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    83,
      41,    87,    43,    45,    46,    50,    51,    48,    49,    89,
       0,    88
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,   105,    38,     8,     9,    17,    43,    76,    50,
      51,    52,    53,    54,   150,   151,   152,   153,   154,    56,
      57,    10,    39,    40,    41,   122,   109,   110,   111,   112
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -67
static const yytype_int16 yypact[] =
{
     233,    47,   -67,   -32,   -67,   142,   -67,   -32,    66,   178,
     -67,   -32,   -67,   -21,   -67,   -67,   -67,    41,    59,   -32,
     -67,   -32,   -67,    82,    99,   222,   -18,   218,   218,   223,
     218,   102,   105,   113,   116,   -18,   218,   -10,   -32,    69,
     -67,     7,    48,   -67,   218,   218,   218,   218,   -67,   -67,
     -67,   237,   -67,    17,   -67,     8,   198,   -67,   265,   -10,
     196,    31,   -18,   218,   -18,   218,   -67,   265,   127,   -67,
      28,   -10,    47,   218,   -67,   -67,   238,   265,   -67,   -67,
     -67,    50,    89,   218,   218,   218,   218,   -67,   218,   218,
     218,   -67,   -10,   -67,   -67,   265,   -67,   265,    12,    54,
      62,    73,   191,   -67,   -67,   -67,   -32,    58,    15,   -67,
     153,   -67,   -67,    88,   -67,   -67,    57,   -67,   206,   -67,
     -67,   265,   203,    74,    92,   198,   198,   -67,   -67,   -67,
     -67,   218,   218,   -67,   -67,   -67,    24,   128,   218,   -67,
     -67,   -67,   -67,   -67,   -67,   265,   -67,   218,   -67,   -67,
      93,   119,   264,   250,   265,   163,   -67,    29,   265,   218,
     179,   218,   218,   218,   218,   218,   218,   218,   179,   -67,
     119,    85,   264,   250,   250,   265,   265,   265,   265,   -67,
     179,   -67
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -67,   -67,   240,     5,   -67,   -67,   220,   -19,   -67,   -67,
      10,   -66,   -67,   -67,    -4,     2,    11,   114,   -27,   193,
     -20,   182,   155,   121,   -67,   -67,   -29,   -67,   110,    38
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      55,    58,   107,    61,    12,     7,    11,    25,    69,    67,
       7,    85,    86,    13,    42,    77,    66,    18,    85,    86,
      81,    24,    68,    75,    78,    79,    80,    85,    86,    32,
      91,    34,    85,    86,    85,    86,    95,    73,    97,    87,
     131,   108,   114,    94,   107,    96,   116,    84,    70,    26,
     139,    44,    45,    85,    86,   121,   123,   124,   113,   156,
      85,    86,    93,   130,   169,    46,   138,    28,   127,   128,
     129,    27,     2,   106,     4,   136,    47,    85,    86,   119,
      42,    74,   132,   108,    12,    48,    49,    29,   143,    30,
      35,   145,    44,    45,   107,    85,    86,   133,    71,   144,
      19,    20,   107,    72,   180,   148,    46,    36,   134,   159,
      62,   157,    27,    63,   107,   106,   137,    47,   120,   142,
     158,    64,   160,   149,    65,    12,    48,    49,   155,    30,
      44,    45,    27,   108,   161,    30,    28,   175,   176,   177,
     178,   108,    14,    27,    46,    98,    30,    99,   100,   101,
     102,     1,     2,   108,     4,    47,    44,    45,    30,    68,
     103,   170,   104,    12,    48,    49,     1,     2,     3,     4,
      46,    98,   172,    99,   100,   101,   102,     1,     2,   159,
       4,    47,    44,    45,    60,    68,   140,    16,   104,    12,
      48,    49,   168,   115,    44,    45,    46,    98,   171,    99,
     100,   101,   102,    88,    89,    90,   179,    47,    46,    44,
      45,    68,    21,    22,   104,    12,    48,    49,   181,    47,
     141,    44,    45,    46,     0,    92,   135,    12,    48,    49,
      72,    23,   146,     0,    47,    46,     0,   147,    42,    31,
       6,    33,    12,    48,    49,    15,    47,     2,     2,     4,
       4,    37,    59,     0,    12,    48,    49,     1,     2,     3,
       4,   164,   165,   166,   167,    82,     0,    83,    85,    86,
       0,   117,   118,   162,   163,     0,   173,   174,   125,   126
};

static const yytype_int16 yycheck[] =
{
      27,    28,    68,    30,    36,     0,     1,    28,    37,    36,
       5,     3,     4,     3,    32,    42,    35,     7,     3,     4,
      47,    11,    32,    42,    44,    45,    46,     3,     4,    19,
      59,    21,     3,     4,     3,     4,    63,    30,    65,    31,
      28,    68,    71,    62,   110,    64,    73,    30,    38,     8,
      35,     3,     4,     3,     4,    82,    83,    84,    30,    35,
       3,     4,    31,    92,    35,    17,     8,     8,    88,    89,
      90,    30,    25,    68,    27,   102,    28,     3,     4,    29,
      32,    33,    28,   110,    36,    37,    38,    28,    31,    30,
       8,   118,     3,     4,   160,     3,     4,    35,    29,   118,
      34,    35,   168,    34,    19,    31,    17,     8,    35,    16,
       8,   138,    30,     8,   180,   110,   106,    28,    29,    31,
     147,     8,    29,    31,     8,    36,    37,    38,   132,    30,
       3,     4,    30,   160,    15,    30,     8,   164,   165,   166,
     167,   168,     0,    30,    17,    18,    30,    20,    21,    22,
      23,    24,    25,   180,    27,    28,     3,     4,    30,    32,
      33,   159,    35,    36,    37,    38,    24,    25,    26,    27,
      17,    18,   161,    20,    21,    22,    23,    24,    25,    16,
      27,    28,     3,     4,    29,    32,    33,     5,    35,    36,
      37,    38,    29,    72,     3,     4,    17,    18,   160,    20,
      21,    22,    23,     5,     6,     7,   168,    28,    17,     3,
       4,    32,    34,    35,    35,    36,    37,    38,   180,    28,
     110,     3,     4,    17,    -1,    29,    35,    36,    37,    38,
      34,    11,    29,    -1,    28,    17,    -1,    34,    32,    19,
       0,    21,    36,    37,    38,     5,    28,    25,    25,    27,
      27,    29,    29,    -1,    36,    37,    38,    24,    25,    26,
      27,    11,    12,    13,    14,    28,    -1,    30,     3,     4,
      -1,    33,    34,     9,    10,    -1,   162,   163,    85,    86
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    24,    25,    26,    27,    40,    41,    42,    43,    44,
      60,    42,    36,    49,     0,    41,    60,    45,    49,    34,
      35,    34,    35,    45,    49,    28,     8,    30,     8,    28,
      30,    45,    49,    45,    49,     8,     8,    29,    42,    61,
      62,    63,    32,    46,     3,     4,    17,    28,    37,    38,
      48,    49,    50,    51,    52,    57,    58,    59,    57,    29,
      61,    57,     8,     8,     8,     8,    46,    57,    32,    65,
      49,    29,    34,    30,    33,    46,    47,    57,    59,    59,
      59,    57,    28,    30,    30,     3,     4,    31,     5,     6,
       7,    65,    29,    31,    46,    57,    46,    57,    18,    20,
      21,    22,    23,    33,    35,    41,    42,    50,    57,    65,
      66,    67,    68,    30,    65,    62,    57,    33,    34,    29,
      29,    57,    64,    57,    57,    58,    58,    59,    59,    59,
      65,    28,    28,    35,    35,    35,    57,    49,     8,    35,
      33,    67,    31,    31,    46,    57,    29,    34,    31,    31,
      53,    54,    55,    56,    57,    53,    35,    57,    57,    16,
      29,    15,     9,    10,    11,    12,    13,    14,    29,    35,
      54,    68,    55,    56,    56,    57,    57,    57,    57,    68,
      19,    68
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 68 "syntax_analyzer.y"
    { 
            (yyval.root) = (yyvsp[(1) - (2)].root); 
            (yyval.root)->declareStatement_.emplace_back((yyvsp[(2) - (2)].declare_statement)); 
            if((yyval.root)->scope_ == nullptr) (yyval.root)->scope_ = new Scope();
      ;}
    break;

  case 3:
#line 73 "syntax_analyzer.y"
    { 
            (yyval.root) = (yyvsp[(1) - (2)].root); 
            (yyval.root)->functionDefinitions_.emplace_back((yyvsp[(2) - (2)].function_definition)); 
            if((yyval.root)->scope_ == nullptr) (yyval.root)->scope_ = new Scope();
            (yyval.root)->scope_->funcDeclares_[(yyvsp[(2) - (2)].function_definition)->identifier_->id_] = (yyvsp[(2) - (2)].function_definition);
            (yyvsp[(2) - (2)].function_definition)->body_->scope_->parent = (yyval.root)->scope_;
      ;}
    break;

  case 4:
#line 80 "syntax_analyzer.y"
    {
            root = new Root(); 
            (yyval.root) = root; 
            (yyval.root)->declareStatement_.emplace_back((yyvsp[(1) - (1)].declare_statement));
            if((yyval.root)->scope_ == nullptr) (yyval.root)->scope_ = new Scope();
      ;}
    break;

  case 5:
#line 86 "syntax_analyzer.y"
    { 
            root = new Root(); 
            (yyval.root) = root; 
            (yyval.root)->functionDefinitions_.emplace_back((yyvsp[(1) - (1)].function_definition)); 
            if((yyval.root)->scope_ == nullptr) (yyval.root)->scope_ = new Scope();
            (yyval.root)->scope_->funcDeclares_[(yyvsp[(1) - (1)].function_definition)->identifier_->id_] = (yyvsp[(1) - (1)].function_definition);
            (yyvsp[(1) - (1)].function_definition)->body_->scope_->parent = (yyval.root)->scope_;
      ;}
    break;

  case 6:
#line 96 "syntax_analyzer.y"
    { (yyval.declare_statement) = (yyvsp[(1) - (2)].declare_statement);;}
    break;

  case 7:
#line 97 "syntax_analyzer.y"
    { (yyval.declare_statement) = (yyvsp[(1) - (2)].declare_statement); ;}
    break;

  case 8:
#line 100 "syntax_analyzer.y"
    { (yyval.type) = SysType::INT; ;}
    break;

  case 9:
#line 101 "syntax_analyzer.y"
    { (yyval.type) = SysType::FLOAT; ;}
    break;

  case 10:
#line 104 "syntax_analyzer.y"
    { 
            (yyval.declare_statement) = new DeclareStatement((yyvsp[(2) - (5)].type)); 
            (yyval.declare_statement)->declares_.emplace_back(new VarDeclare{(yyvsp[(2) - (5)].type), (yyvsp[(3) - (5)].ident), (yyvsp[(5) - (5)].expr), true}); 
      ;}
    break;

  case 11:
#line 108 "syntax_analyzer.y"
    { 
            (yyval.declare_statement) = (yyvsp[(1) - (5)].declare_statement); 
            (yyval.declare_statement)->declares_.emplace_back(new VarDeclare{(yyvsp[(1) - (5)].declare_statement)->getType(),(yyvsp[(3) - (5)].ident), (yyvsp[(5) - (5)].expr), true}); 
      ;}
    break;

  case 12:
#line 112 "syntax_analyzer.y"
    { 
            (yyval.declare_statement) = new DeclareStatement((yyvsp[(2) - (5)].type)); 
            (yyval.declare_statement)->declares_.emplace_back(new ArrayDeclare{(yyvsp[(2) - (5)].type), (yyvsp[(3) - (5)].ident), (yyvsp[(5) - (5)].array_val), true}); 
      ;}
    break;

  case 13:
#line 116 "syntax_analyzer.y"
    { 
            (yyval.declare_statement) = (yyvsp[(1) - (5)].declare_statement); 
            (yyval.declare_statement)->declares_.emplace_back(new ArrayDeclare{(yyvsp[(1) - (5)].declare_statement)->getType(), (yyvsp[(3) - (5)].ident), (yyvsp[(5) - (5)].array_val), true}); 
      ;}
    break;

  case 14:
#line 122 "syntax_analyzer.y"
    { 
            (yyval.declare_statement) = new DeclareStatement((yyvsp[(1) - (2)].type)); 
            (yyval.declare_statement)->declares_.emplace_back(new VarDeclare((yyvsp[(1) - (2)].type), (yyvsp[(2) - (2)].ident), nullptr, false)); 
      ;}
    break;

  case 15:
#line 126 "syntax_analyzer.y"
    { 
            (yyval.declare_statement) = new DeclareStatement((yyvsp[(1) - (4)].type)); 
            (yyval.declare_statement)->declares_.emplace_back(new VarDeclare((yyvsp[(1) - (4)].type), (yyvsp[(2) - (4)].ident), (yyvsp[(4) - (4)].expr), false)); 
      ;}
    break;

  case 16:
#line 130 "syntax_analyzer.y"
    { 
            (yyval.declare_statement) = new DeclareStatement((yyvsp[(1) - (2)].type)); 
            (yyval.declare_statement)->declares_.emplace_back(new ArrayDeclare((yyvsp[(1) - (2)].type), (yyvsp[(2) - (2)].ident), nullptr, false)); 
      ;}
    break;

  case 17:
#line 134 "syntax_analyzer.y"
    { 
            (yyval.declare_statement) = new DeclareStatement((yyvsp[(1) - (4)].type)); 
            (yyval.declare_statement)->declares_.emplace_back(new ArrayDeclare((yyvsp[(1) - (4)].type), (yyvsp[(2) - (4)].ident), (yyvsp[(4) - (4)].array_val), false)); 
      ;}
    break;

  case 18:
#line 138 "syntax_analyzer.y"
    { 
            (yyval.declare_statement) = (yyvsp[(1) - (3)].declare_statement); 
            (yyval.declare_statement)->declares_.emplace_back(new VarDeclare((yyvsp[(1) - (3)].declare_statement)->getType(), (yyvsp[(3) - (3)].ident), nullptr, false)); 
      ;}
    break;

  case 19:
#line 142 "syntax_analyzer.y"
    { 
            (yyval.declare_statement) = (yyvsp[(1) - (5)].declare_statement); 
            (yyval.declare_statement)->declares_.emplace_back(new VarDeclare((yyvsp[(1) - (5)].declare_statement)->getType(), (yyvsp[(3) - (5)].ident), (yyvsp[(5) - (5)].expr), false)); 
      ;}
    break;

  case 20:
#line 146 "syntax_analyzer.y"
    { 
            (yyval.declare_statement) = (yyvsp[(1) - (3)].declare_statement); 
            (yyval.declare_statement)->declares_.emplace_back(new ArrayDeclare((yyvsp[(1) - (3)].declare_statement)->getType(),(yyvsp[(3) - (3)].ident), nullptr, false)); 
      ;}
    break;

  case 21:
#line 150 "syntax_analyzer.y"
    { 
            (yyval.declare_statement) = (yyvsp[(1) - (5)].declare_statement); 
            (yyval.declare_statement)->declares_.emplace_back(new ArrayDeclare((yyvsp[(1) - (5)].declare_statement)->getType(), (yyvsp[(3) - (5)].ident), (yyvsp[(5) - (5)].array_val), false)); 
      ;}
    break;

  case 22:
#line 156 "syntax_analyzer.y"
    { (yyval.ident) = (yyvsp[(1) - (4)].ident); (yyval.ident)->dimension_.emplace_back((yyvsp[(3) - (4)].expr)); ;}
    break;

  case 23:
#line 157 "syntax_analyzer.y"
    { (yyval.ident) = (yyvsp[(1) - (4)].ident); (yyval.ident)->dimension_.emplace_back((yyvsp[(3) - (4)].expr)); ;}
    break;

  case 24:
#line 160 "syntax_analyzer.y"
    { (yyval.array_val) = new ArrayValue(false, nullptr); ;}
    break;

  case 25:
#line 161 "syntax_analyzer.y"
    { (yyval.array_val) = (yyvsp[(2) - (3)].array_val); ;}
    break;

  case 26:
#line 163 "syntax_analyzer.y"
    { 
            (yyval.array_val) = new ArrayValue(false, nullptr); 
            (yyval.array_val)->valueList_.emplace_back(new ArrayValue(true, (yyvsp[(1) - (1)].expr))); 
      ;}
    break;

  case 27:
#line 167 "syntax_analyzer.y"
    {
            (yyval.array_val) = new ArrayValue(false, nullptr);
            (yyval.array_val)->valueList_.emplace_back((yyvsp[(1) - (1)].array_val)); 
      ;}
    break;

  case 28:
#line 171 "syntax_analyzer.y"
    {
            (yyval.array_val) = (yyvsp[(1) - (3)].array_val);
            (yyval.array_val)->valueList_.emplace_back(new ArrayValue(true, (yyvsp[(3) - (3)].expr)));
      ;}
    break;

  case 29:
#line 175 "syntax_analyzer.y"
    {
            (yyval.array_val) = (yyvsp[(1) - (3)].array_val);
            (yyval.array_val)->valueList_.emplace_back((yyvsp[(3) - (3)].array_val));
      ;}
    break;

  case 30:
#line 180 "syntax_analyzer.y"
    { (yyval.expr) = new Number(SysType::INT, (yyvsp[(1) - (1)].token)); ;}
    break;

  case 31:
#line 181 "syntax_analyzer.y"
    { (yyval.expr) = new Number(SysType::FLOAT, (yyvsp[(1) - (1)].f_val)); ;}
    break;

  case 32:
#line 184 "syntax_analyzer.y"
    { (yyval.ident) = new Identifier((yyvsp[(1) - (1)].string)); ;}
    break;

  case 33:
#line 187 "syntax_analyzer.y"
    { (yyval.expr) = new LValExpression((yyvsp[(1) - (1)].ident)); ;}
    break;

  case 34:
#line 188 "syntax_analyzer.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 35:
#line 191 "syntax_analyzer.y"
    { 
            (yyval.expr) = new LValExpression((yyvsp[(1) - (4)].ident));
            dynamic_cast<LValExpression*>((yyval.expr))->identifier_->dimension_.emplace_back((yyvsp[(3) - (4)].expr));
      ;}
    break;

  case 36:
#line 195 "syntax_analyzer.y"
    { 
            (yyval.expr) = (yyvsp[(1) - (4)].expr);
            dynamic_cast<LValExpression*>((yyval.expr))->identifier_->dimension_.emplace_back((yyvsp[(3) - (4)].expr));
      ;}
    break;

  case 37:
#line 201 "syntax_analyzer.y"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr); ;}
    break;

  case 38:
#line 202 "syntax_analyzer.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 39:
#line 203 "syntax_analyzer.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 40:
#line 206 "syntax_analyzer.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 41:
#line 207 "syntax_analyzer.y"
    { (yyval.expr) = new BinaryExpression((yyvsp[(1) - (3)].expr), BinaryOp::OR, (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 42:
#line 210 "syntax_analyzer.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 43:
#line 211 "syntax_analyzer.y"
    { (yyval.expr) = new BinaryExpression((yyvsp[(1) - (3)].expr), BinaryOp::AND, (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 44:
#line 214 "syntax_analyzer.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 45:
#line 215 "syntax_analyzer.y"
    { (yyval.expr) = new BinaryExpression((yyvsp[(1) - (3)].expr), BinaryOp::EQ, (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 46:
#line 216 "syntax_analyzer.y"
    { (yyval.expr) = new BinaryExpression((yyvsp[(1) - (3)].expr), BinaryOp::NEQ, (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 47:
#line 219 "syntax_analyzer.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 48:
#line 220 "syntax_analyzer.y"
    { (yyval.expr) = new BinaryExpression((yyvsp[(1) - (3)].expr), BinaryOp::GT, (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 49:
#line 221 "syntax_analyzer.y"
    { (yyval.expr) = new BinaryExpression((yyvsp[(1) - (3)].expr), BinaryOp::GTE, (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 50:
#line 222 "syntax_analyzer.y"
    { (yyval.expr) = new BinaryExpression((yyvsp[(1) - (3)].expr), BinaryOp::LT, (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 51:
#line 223 "syntax_analyzer.y"
    { (yyval.expr) = new BinaryExpression((yyvsp[(1) - (3)].expr), BinaryOp::LTE, (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 52:
#line 226 "syntax_analyzer.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 53:
#line 227 "syntax_analyzer.y"
    { (yyval.expr) = new BinaryExpression((yyvsp[(1) - (3)].expr), BinaryOp::ADD, (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 54:
#line 228 "syntax_analyzer.y"
    { (yyval.expr) = new BinaryExpression((yyvsp[(1) - (3)].expr), BinaryOp::SUB, (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 55:
#line 231 "syntax_analyzer.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 56:
#line 232 "syntax_analyzer.y"
    { (yyval.expr) = new BinaryExpression((yyvsp[(1) - (3)].expr), BinaryOp::MUL, (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 57:
#line 233 "syntax_analyzer.y"
    { (yyval.expr) = new BinaryExpression((yyvsp[(1) - (3)].expr), BinaryOp::DIV, (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 58:
#line 234 "syntax_analyzer.y"
    { (yyval.expr) = new BinaryExpression((yyvsp[(1) - (3)].expr), BinaryOp::MOD, (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 59:
#line 237 "syntax_analyzer.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 60:
#line 238 "syntax_analyzer.y"
    { 
            (yyval.expr) = new FuncCallExpression((yyvsp[(1) - (3)].ident), nullptr); 
      ;}
    break;

  case 61:
#line 241 "syntax_analyzer.y"
    { 
            (yyval.expr) = new FuncCallExpression((yyvsp[(1) - (4)].ident), (yyvsp[(3) - (4)].actual_args)); 
      ;}
    break;

  case 62:
#line 244 "syntax_analyzer.y"
    { (yyval.expr) = new UnaryExpression(UnaryOp::POSITIVE, (yyvsp[(2) - (2)].expr)); ;}
    break;

  case 63:
#line 245 "syntax_analyzer.y"
    { (yyval.expr) = new UnaryExpression(UnaryOp::NEGATIVE, (yyvsp[(2) - (2)].expr)); ;}
    break;

  case 64:
#line 246 "syntax_analyzer.y"
    { (yyval.expr) = new UnaryExpression(UnaryOp::NOT, (yyvsp[(2) - (2)].expr)); ;}
    break;

  case 65:
#line 249 "syntax_analyzer.y"
    { 
            (yyval.function_definition) = new FunctionDefinition((yyvsp[(1) - (5)].type), (yyvsp[(2) - (5)].ident), new FormalArgumentList(), (yyvsp[(5) - (5)].block));  
      ;}
    break;

  case 66:
#line 252 "syntax_analyzer.y"
    { 
            (yyval.function_definition) = new FunctionDefinition((yyvsp[(1) - (6)].type), (yyvsp[(2) - (6)].ident), (yyvsp[(4) - (6)].formal_args), (yyvsp[(6) - (6)].block)); 
      ;}
    break;

  case 67:
#line 255 "syntax_analyzer.y"
    { 
            (yyval.function_definition) = new FunctionDefinition(SysType::VOID, (yyvsp[(2) - (5)].ident), new FormalArgumentList(), (yyvsp[(5) - (5)].block)); 
      ;}
    break;

  case 68:
#line 258 "syntax_analyzer.y"
    { 
            (yyval.function_definition) = new FunctionDefinition(SysType::VOID, (yyvsp[(2) - (6)].ident), (yyvsp[(4) - (6)].formal_args), (yyvsp[(6) - (6)].block)); 
      ;}
    break;

  case 69:
#line 263 "syntax_analyzer.y"
    { 
            (yyval.formal_args) = new FormalArgumentList(); 
            (yyval.formal_args)->list_.emplace_back((yyvsp[(1) - (1)].formal_arg)); 
      ;}
    break;

  case 70:
#line 267 "syntax_analyzer.y"
    { 
            (yyval.formal_args) = (yyvsp[(1) - (3)].formal_args);
            (yyval.formal_args)->list_.emplace_back((yyvsp[(3) - (3)].formal_arg)); 
      ;}
    break;

  case 71:
#line 273 "syntax_analyzer.y"
    { (yyval.formal_arg) = new FormalArgument((yyvsp[(1) - (2)].type), (yyvsp[(2) - (2)].ident)); ;}
    break;

  case 73:
#line 277 "syntax_analyzer.y"
    {
            (yyval.formal_arg) = new FormalArgument((yyvsp[(1) - (4)].type), (yyvsp[(2) - (4)].ident));
            (yyval.formal_arg)->identifier_->dimension_.emplace_back(nullptr);
      ;}
    break;

  case 74:
#line 281 "syntax_analyzer.y"
    { 
            (yyval.formal_arg) = (yyvsp[(1) - (4)].formal_arg);
            (yyval.formal_arg)->identifier_->dimension_.emplace_back((yyvsp[(3) - (4)].expr));
      ;}
    break;

  case 75:
#line 287 "syntax_analyzer.y"
    { (yyval.actual_args) = new ActualArgumentList(); (yyval.actual_args)->list_.emplace_back((yyvsp[(1) - (1)].expr)); ;}
    break;

  case 76:
#line 288 "syntax_analyzer.y"
    { (yyval.actual_args) = (yyvsp[(1) - (3)].actual_args); (yyval.actual_args)->list_.emplace_back((yyvsp[(3) - (3)].expr)); ;}
    break;

  case 77:
#line 291 "syntax_analyzer.y"
    { (yyval.block) = new Block();
            if((yyval.block)->scope_ == nullptr) (yyval.block)->scope_ = new Scope();
      ;}
    break;

  case 78:
#line 294 "syntax_analyzer.y"
    { 
            (yyval.block) = (yyvsp[(2) - (3)].block); 
            if((yyval.block)->scope_ == nullptr) (yyval.block)->scope_ = new Scope();
            for(auto&stmt : (yyvsp[(2) - (3)].block)->statements_) {
                if(stmt->statement_type() == StmtType::BLOCK) {
                  dynamic_cast<Block*>(stmt)->scope_->parent = (yyval.block)->scope_;
                }
                else if(stmt->statement_type() == StmtType::IFELSE) {
                  auto ifelse_stmt = dynamic_cast<IfElseStatement*>(stmt);
                  ifelse_stmt->scope_->parent = (yyval.block)->scope_;
                }
                else if(stmt->statement_type() == StmtType::WHILE) {
                  auto while_stmt = dynamic_cast<WhileStatement*>(stmt);
                  while_stmt->scope_->parent = (yyval.block)->scope_;
                }
                else continue;
            }
      ;}
    break;

  case 79:
#line 314 "syntax_analyzer.y"
    { 
            (yyval.block) = new Block(); 
            if ((yyvsp[(1) - (1)].stmt) != nullptr) (yyval.block)->statements_.emplace_back((yyvsp[(1) - (1)].stmt)); 
      ;}
    break;

  case 80:
#line 318 "syntax_analyzer.y"
    { 
            (yyval.block) = (yyvsp[(1) - (2)].block); 
            if ((yyvsp[(1) - (2)].block) != nullptr) (yyval.block)->statements_.emplace_back((yyvsp[(2) - (2)].stmt)); 
      ;}
    break;

  case 81:
#line 324 "syntax_analyzer.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].declare_statement); ;}
    break;

  case 82:
#line 325 "syntax_analyzer.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 83:
#line 328 "syntax_analyzer.y"
    { (yyval.stmt) = new AssignStatement((yyvsp[(1) - (4)].expr), (yyvsp[(3) - (4)].expr)); ;}
    break;

  case 84:
#line 329 "syntax_analyzer.y"
    { (yyval.stmt) = nullptr; ;}
    break;

  case 85:
#line 330 "syntax_analyzer.y"
    { (yyval.stmt) = new EvalStatement((yyvsp[(1) - (2)].expr)); ;}
    break;

  case 86:
#line 331 "syntax_analyzer.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].block); ;}
    break;

  case 87:
#line 332 "syntax_analyzer.y"
    { 
            (yyval.stmt) = new IfElseStatement((yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].stmt), nullptr); 
            if ((yyvsp[(5) - (5)].stmt)->statement_type() == StmtType::BLOCK)
               dynamic_cast<Block*>((yyvsp[(5) - (5)].stmt))->scope_->parent = dynamic_cast<IfElseStatement*>((yyval.stmt))->scope_;   
            else if ((yyvsp[(5) - (5)].stmt)->statement_type() == StmtType::IFELSE)
               dynamic_cast<IfElseStatement*>((yyvsp[(5) - (5)].stmt))->scope_->parent = dynamic_cast<IfElseStatement*>((yyval.stmt))->scope_;   
            else if ((yyvsp[(5) - (5)].stmt)->statement_type() == StmtType::WHILE)
               dynamic_cast<WhileStatement*>((yyvsp[(5) - (5)].stmt))->scope_->parent = dynamic_cast<IfElseStatement*>((yyval.stmt))->scope_;   
      ;}
    break;

  case 88:
#line 341 "syntax_analyzer.y"
    { 
            (yyval.stmt) = new IfElseStatement((yyvsp[(3) - (7)].expr), (yyvsp[(5) - (7)].stmt), (yyvsp[(7) - (7)].stmt)); 
            if ((yyvsp[(5) - (7)].stmt)->statement_type() == StmtType::BLOCK)
               dynamic_cast<Block*>((yyvsp[(5) - (7)].stmt))->scope_->parent = dynamic_cast<IfElseStatement*>((yyval.stmt))->scope_;   
            else if ((yyvsp[(5) - (7)].stmt)->statement_type() == StmtType::IFELSE)
               dynamic_cast<IfElseStatement*>((yyvsp[(5) - (7)].stmt))->scope_->parent = dynamic_cast<IfElseStatement*>((yyval.stmt))->scope_;   
            else if ((yyvsp[(5) - (7)].stmt)->statement_type() == StmtType::WHILE)
               dynamic_cast<WhileStatement*>((yyvsp[(5) - (7)].stmt))->scope_->parent = dynamic_cast<IfElseStatement*>((yyval.stmt))->scope_;   
            if ((yyvsp[(7) - (7)].stmt)->statement_type() == StmtType::BLOCK)
               dynamic_cast<Block*>((yyvsp[(7) - (7)].stmt))->scope_->parent = dynamic_cast<IfElseStatement*>((yyval.stmt))->scope_;   
            else if ((yyvsp[(7) - (7)].stmt)->statement_type() == StmtType::IFELSE)
               dynamic_cast<IfElseStatement*>((yyvsp[(7) - (7)].stmt))->scope_->parent = dynamic_cast<IfElseStatement*>((yyval.stmt))->scope_;   
            else if ((yyvsp[(7) - (7)].stmt)->statement_type() == StmtType::WHILE)
               dynamic_cast<WhileStatement*>((yyvsp[(7) - (7)].stmt))->scope_->parent = dynamic_cast<IfElseStatement*>((yyval.stmt))->scope_;   
      ;}
    break;

  case 89:
#line 356 "syntax_analyzer.y"
    { 
            (yyval.stmt) = new WhileStatement((yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].stmt)); 
            if ((yyvsp[(5) - (5)].stmt)->statement_type() == StmtType::BLOCK)
               dynamic_cast<Block*>((yyvsp[(5) - (5)].stmt))->scope_->parent = dynamic_cast<WhileStatement*>((yyval.stmt))->scope_;   
            else if ((yyvsp[(5) - (5)].stmt)->statement_type() == StmtType::IFELSE)
               dynamic_cast<IfElseStatement*>((yyvsp[(5) - (5)].stmt))->scope_->parent = dynamic_cast<WhileStatement*>((yyval.stmt))->scope_;   
            else if ((yyvsp[(5) - (5)].stmt)->statement_type() == StmtType::WHILE)
               dynamic_cast<WhileStatement*>((yyvsp[(5) - (5)].stmt))->scope_->parent = dynamic_cast<WhileStatement*>((yyval.stmt))->scope_;   
      ;}
    break;

  case 90:
#line 365 "syntax_analyzer.y"
    { (yyval.stmt) = new BreakStatement(); ;}
    break;

  case 91:
#line 366 "syntax_analyzer.y"
    { (yyval.stmt) = new ContinueStatement(); ;}
    break;

  case 92:
#line 367 "syntax_analyzer.y"
    { (yyval.stmt) = new ReturnStatement(); ;}
    break;

  case 93:
#line 368 "syntax_analyzer.y"
    { (yyval.stmt) = new ReturnStatement((yyvsp[(2) - (3)].expr)); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2242 "syntax_analyzer.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



