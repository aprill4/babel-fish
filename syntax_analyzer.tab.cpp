/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "syntax_analyzer.y"

#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
//#include "syntax_analyzer.tab.h"
Root* root = nullptr;

extern int yylex(void);

extern "C" void yyerror(const char *s);


#line 83 "syntax_analyzer.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
#line 17 "syntax_analyzer.y"

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

#line 193 "syntax_analyzer.tab.c"

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



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

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
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  182

#define YYUNDEFTOK  2
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    66,    66,    71,    78,    84,    94,    95,    98,    99,
     102,   106,   110,   114,   120,   124,   128,   132,   136,   140,
     144,   148,   154,   155,   158,   159,   161,   165,   169,   173,
     178,   179,   182,   185,   186,   189,   193,   199,   200,   201,
     204,   205,   208,   209,   212,   213,   214,   217,   218,   219,
     220,   221,   224,   225,   226,   229,   230,   231,   232,   235,
     236,   239,   242,   243,   244,   247,   250,   253,   256,   261,
     265,   271,   272,   275,   279,   285,   286,   289,   292,   314,
     318,   324,   325,   328,   329,   330,   331,   332,   343,   362,
     373,   374,   375,   376
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
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
  "FuncRParams", "Block", "BlockItems", "BlockItem", "Stmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293
};
# endif

#define YYPACT_NINF (-67)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
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

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
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

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -67,   -67,   240,     5,   -67,   -67,   220,   -19,   -67,   -67,
      10,   -66,   -67,   -67,    -4,     2,    11,   114,   -27,   193,
     -20,   182,   155,   121,   -67,   -67,   -29,   -67,   110,    38
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,   105,    38,     8,     9,    17,    43,    76,    50,
      51,    52,    53,    54,   150,   151,   152,   153,   154,    56,
      57,    10,    39,    40,    41,   122,   109,   110,   111,   112
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
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
static const yytype_int8 yystos[] =
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

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
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

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
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


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 66 "syntax_analyzer.y"
                        { 
            (yyval.root) = (yyvsp[-1].root); 
            (yyval.root)->declareStatement_.emplace_back((yyvsp[0].declare_statement)); 
            if((yyval.root)->scope_ == nullptr) (yyval.root)->scope_ = new Scope();
      }
#line 1626 "syntax_analyzer.tab.c"
    break;

  case 3:
#line 71 "syntax_analyzer.y"
                         { 
            (yyval.root) = (yyvsp[-1].root); 
            (yyval.root)->functionDefinitions_.emplace_back((yyvsp[0].function_definition)); 
            if((yyval.root)->scope_ == nullptr) (yyval.root)->scope_ = new Scope();
            (yyval.root)->scope_->funcDeclares_[(yyvsp[0].function_definition)->identifier_->id_] = (yyvsp[0].function_definition);
            (yyvsp[0].function_definition)->body_->scope_->parent = (yyval.root)->scope_;
      }
#line 1638 "syntax_analyzer.tab.c"
    break;

  case 4:
#line 78 "syntax_analyzer.y"
             {
            root = new Root(); 
            (yyval.root) = root; 
            (yyval.root)->declareStatement_.emplace_back((yyvsp[0].declare_statement));
            if((yyval.root)->scope_ == nullptr) (yyval.root)->scope_ = new Scope();
      }
#line 1649 "syntax_analyzer.tab.c"
    break;

  case 5:
#line 84 "syntax_analyzer.y"
                { 
            root = new Root(); 
            (yyval.root) = root; 
            (yyval.root)->functionDefinitions_.emplace_back((yyvsp[0].function_definition)); 
            if((yyval.root)->scope_ == nullptr) (yyval.root)->scope_ = new Scope();
            (yyval.root)->scope_->funcDeclares_[(yyvsp[0].function_definition)->identifier_->id_] = (yyvsp[0].function_definition);
            (yyvsp[0].function_definition)->body_->scope_->parent = (yyval.root)->scope_;
      }
#line 1662 "syntax_analyzer.tab.c"
    break;

  case 6:
#line 94 "syntax_analyzer.y"
                          { (yyval.declare_statement) = (yyvsp[-1].declare_statement);}
#line 1668 "syntax_analyzer.tab.c"
    break;

  case 7:
#line 95 "syntax_analyzer.y"
                        { (yyval.declare_statement) = (yyvsp[-1].declare_statement); }
#line 1674 "syntax_analyzer.tab.c"
    break;

  case 8:
#line 98 "syntax_analyzer.y"
           { (yyval.type) = SysType::INT; }
#line 1680 "syntax_analyzer.tab.c"
    break;

  case 9:
#line 99 "syntax_analyzer.y"
            { (yyval.type) = SysType::FLOAT; }
#line 1686 "syntax_analyzer.tab.c"
    break;

  case 10:
#line 102 "syntax_analyzer.y"
                                           { 
            (yyval.declare_statement) = new DeclareStatement((yyvsp[-3].type)); 
            (yyval.declare_statement)->declares_.emplace_back(new VarDeclare{(yyvsp[-3].type), (yyvsp[-2].ident), (yyvsp[0].expr), true}); 
      }
#line 1695 "syntax_analyzer.tab.c"
    break;

  case 11:
#line 106 "syntax_analyzer.y"
                                            { 
            (yyval.declare_statement) = (yyvsp[-4].declare_statement); 
            (yyval.declare_statement)->declares_.emplace_back(new VarDeclare{(yyvsp[-4].declare_statement)->getType(),(yyvsp[-2].ident), (yyvsp[0].expr), true}); 
      }
#line 1704 "syntax_analyzer.tab.c"
    break;

  case 12:
#line 110 "syntax_analyzer.y"
                                               { 
            (yyval.declare_statement) = new DeclareStatement((yyvsp[-3].type)); 
            (yyval.declare_statement)->declares_.emplace_back(new ArrayDeclare{(yyvsp[-3].type), (yyvsp[-2].ident), (yyvsp[0].array_val), true}); 
      }
#line 1713 "syntax_analyzer.tab.c"
    break;

  case 13:
#line 114 "syntax_analyzer.y"
                                                   { 
            (yyval.declare_statement) = (yyvsp[-4].declare_statement); 
            (yyval.declare_statement)->declares_.emplace_back(new ArrayDeclare{(yyvsp[-4].declare_statement)->getType(), (yyvsp[-2].ident), (yyvsp[0].array_val), true}); 
      }
#line 1722 "syntax_analyzer.tab.c"
    break;

  case 14:
#line 120 "syntax_analyzer.y"
                     { 
            (yyval.declare_statement) = new DeclareStatement((yyvsp[-1].type)); 
            (yyval.declare_statement)->declares_.emplace_back(new VarDeclare((yyvsp[-1].type), (yyvsp[0].ident), nullptr, false)); 
      }
#line 1731 "syntax_analyzer.tab.c"
    break;

  case 15:
#line 124 "syntax_analyzer.y"
                                  { 
            (yyval.declare_statement) = new DeclareStatement((yyvsp[-3].type)); 
            (yyval.declare_statement)->declares_.emplace_back(new VarDeclare((yyvsp[-3].type), (yyvsp[-2].ident), (yyvsp[0].expr), false)); 
      }
#line 1740 "syntax_analyzer.tab.c"
    break;

  case 16:
#line 128 "syntax_analyzer.y"
                         { 
            (yyval.declare_statement) = new DeclareStatement((yyvsp[-1].type)); 
            (yyval.declare_statement)->declares_.emplace_back(new ArrayDeclare((yyvsp[-1].type), (yyvsp[0].ident), nullptr, false)); 
      }
#line 1749 "syntax_analyzer.tab.c"
    break;

  case 17:
#line 132 "syntax_analyzer.y"
                                         { 
            (yyval.declare_statement) = new DeclareStatement((yyvsp[-3].type)); 
            (yyval.declare_statement)->declares_.emplace_back(new ArrayDeclare((yyvsp[-3].type), (yyvsp[-2].ident), (yyvsp[0].array_val), false)); 
      }
#line 1758 "syntax_analyzer.tab.c"
    break;

  case 18:
#line 136 "syntax_analyzer.y"
                            { 
            (yyval.declare_statement) = (yyvsp[-2].declare_statement); 
            (yyval.declare_statement)->declares_.emplace_back(new VarDeclare((yyvsp[-2].declare_statement)->getType(), (yyvsp[0].ident), nullptr, false)); 
      }
#line 1767 "syntax_analyzer.tab.c"
    break;

  case 19:
#line 140 "syntax_analyzer.y"
                                          { 
            (yyval.declare_statement) = (yyvsp[-4].declare_statement); 
            (yyval.declare_statement)->declares_.emplace_back(new VarDeclare((yyvsp[-4].declare_statement)->getType(), (yyvsp[-2].ident), (yyvsp[0].expr), false)); 
      }
#line 1776 "syntax_analyzer.tab.c"
    break;

  case 20:
#line 144 "syntax_analyzer.y"
                                 { 
            (yyval.declare_statement) = (yyvsp[-2].declare_statement); 
            (yyval.declare_statement)->declares_.emplace_back(new ArrayDeclare((yyvsp[-2].declare_statement)->getType(),(yyvsp[0].ident), nullptr, false)); 
      }
#line 1785 "syntax_analyzer.tab.c"
    break;

  case 21:
#line 148 "syntax_analyzer.y"
                                                 { 
            (yyval.declare_statement) = (yyvsp[-4].declare_statement); 
            (yyval.declare_statement)->declares_.emplace_back(new ArrayDeclare((yyvsp[-4].declare_statement)->getType(), (yyvsp[-2].ident), (yyvsp[0].array_val), false)); 
      }
#line 1794 "syntax_analyzer.tab.c"
    break;

  case 22:
#line 154 "syntax_analyzer.y"
                                                      { (yyval.ident) = (yyvsp[-3].ident); (yyval.ident)->dimension_.emplace_back((yyvsp[-1].expr)); }
#line 1800 "syntax_analyzer.tab.c"
    break;

  case 23:
#line 155 "syntax_analyzer.y"
                                                       { (yyval.ident) = (yyvsp[-3].ident); (yyval.ident)->dimension_.emplace_back((yyvsp[-1].expr)); }
#line 1806 "syntax_analyzer.tab.c"
    break;

  case 24:
#line 158 "syntax_analyzer.y"
                                   { (yyval.array_val) = new ArrayValue(false, nullptr); }
#line 1812 "syntax_analyzer.tab.c"
    break;

  case 25:
#line 159 "syntax_analyzer.y"
                                           { (yyval.array_val) = (yyvsp[-1].array_val); }
#line 1818 "syntax_analyzer.tab.c"
    break;

  case 26:
#line 161 "syntax_analyzer.y"
                   { 
            (yyval.array_val) = new ArrayValue(false, nullptr); 
            (yyval.array_val)->valueList_.emplace_back(new ArrayValue(true, (yyvsp[0].expr))); 
      }
#line 1827 "syntax_analyzer.tab.c"
    break;

  case 27:
#line 165 "syntax_analyzer.y"
                 {
            (yyval.array_val) = new ArrayValue(false, nullptr);
            (yyval.array_val)->valueList_.emplace_back((yyvsp[0].array_val)); 
      }
#line 1836 "syntax_analyzer.tab.c"
    break;

  case 28:
#line 169 "syntax_analyzer.y"
                               {
            (yyval.array_val) = (yyvsp[-2].array_val);
            (yyval.array_val)->valueList_.emplace_back(new ArrayValue(true, (yyvsp[0].expr)));
      }
#line 1845 "syntax_analyzer.tab.c"
    break;

  case 29:
#line 173 "syntax_analyzer.y"
                                 {
            (yyval.array_val) = (yyvsp[-2].array_val);
            (yyval.array_val)->valueList_.emplace_back((yyvsp[0].array_val));
      }
#line 1854 "syntax_analyzer.tab.c"
    break;

  case 30:
#line 178 "syntax_analyzer.y"
                { (yyval.expr) = new Number(SysType::INT, (yyvsp[0].token)); }
#line 1860 "syntax_analyzer.tab.c"
    break;

  case 31:
#line 179 "syntax_analyzer.y"
                   { (yyval.expr) = new Number(SysType::FLOAT, (yyvsp[0].f_val)); }
#line 1866 "syntax_analyzer.tab.c"
    break;

  case 32:
#line 182 "syntax_analyzer.y"
                  { (yyval.ident) = new Identifier((yyvsp[0].string)); }
#line 1872 "syntax_analyzer.tab.c"
    break;

  case 33:
#line 185 "syntax_analyzer.y"
            { (yyval.expr) = new LValExpression((yyvsp[0].ident)); }
#line 1878 "syntax_analyzer.tab.c"
    break;

  case 34:
#line 186 "syntax_analyzer.y"
                  { (yyval.expr) = (yyvsp[0].expr); }
#line 1884 "syntax_analyzer.tab.c"
    break;

  case 35:
#line 189 "syntax_analyzer.y"
                                                     { 
            (yyval.expr) = new LValExpression((yyvsp[-3].ident));
            dynamic_cast<LValExpression*>((yyval.expr))->identifier_->dimension_.emplace_back((yyvsp[-1].expr));
      }
#line 1893 "syntax_analyzer.tab.c"
    break;

  case 36:
#line 193 "syntax_analyzer.y"
                                                      { 
            (yyval.expr) = (yyvsp[-3].expr);
            dynamic_cast<LValExpression*>((yyval.expr))->identifier_->dimension_.emplace_back((yyvsp[-1].expr));
      }
#line 1902 "syntax_analyzer.tab.c"
    break;

  case 37:
#line 199 "syntax_analyzer.y"
                                                      { (yyval.expr) = (yyvsp[-1].expr); }
#line 1908 "syntax_analyzer.tab.c"
    break;

  case 38:
#line 200 "syntax_analyzer.y"
             { (yyval.expr) = (yyvsp[0].expr); }
#line 1914 "syntax_analyzer.tab.c"
    break;

  case 39:
#line 201 "syntax_analyzer.y"
               { (yyval.expr) = (yyvsp[0].expr); }
#line 1920 "syntax_analyzer.tab.c"
    break;

  case 40:
#line 204 "syntax_analyzer.y"
                { (yyval.expr) = (yyvsp[0].expr); }
#line 1926 "syntax_analyzer.tab.c"
    break;

  case 41:
#line 205 "syntax_analyzer.y"
                          { (yyval.expr) = new BinaryExpression((yyvsp[-2].expr), BinaryOp::OR, (yyvsp[0].expr)); }
#line 1932 "syntax_analyzer.tab.c"
    break;

  case 42:
#line 208 "syntax_analyzer.y"
               { (yyval.expr) = (yyvsp[0].expr); }
#line 1938 "syntax_analyzer.tab.c"
    break;

  case 43:
#line 209 "syntax_analyzer.y"
                           { (yyval.expr) = new BinaryExpression((yyvsp[-2].expr), BinaryOp::AND, (yyvsp[0].expr)); }
#line 1944 "syntax_analyzer.tab.c"
    break;

  case 44:
#line 212 "syntax_analyzer.y"
              { (yyval.expr) = (yyvsp[0].expr); }
#line 1950 "syntax_analyzer.tab.c"
    break;

  case 45:
#line 213 "syntax_analyzer.y"
                        { (yyval.expr) = new BinaryExpression((yyvsp[-2].expr), BinaryOp::EQ, (yyvsp[0].expr)); }
#line 1956 "syntax_analyzer.tab.c"
    break;

  case 46:
#line 214 "syntax_analyzer.y"
                         { (yyval.expr) = new BinaryExpression((yyvsp[-2].expr), BinaryOp::NEQ, (yyvsp[0].expr)); }
#line 1962 "syntax_analyzer.tab.c"
    break;

  case 47:
#line 217 "syntax_analyzer.y"
               { (yyval.expr) = (yyvsp[0].expr); }
#line 1968 "syntax_analyzer.tab.c"
    break;

  case 48:
#line 218 "syntax_analyzer.y"
                          { (yyval.expr) = new BinaryExpression((yyvsp[-2].expr), BinaryOp::GT, (yyvsp[0].expr)); }
#line 1974 "syntax_analyzer.tab.c"
    break;

  case 49:
#line 219 "syntax_analyzer.y"
                           { (yyval.expr) = new BinaryExpression((yyvsp[-2].expr), BinaryOp::GTE, (yyvsp[0].expr)); }
#line 1980 "syntax_analyzer.tab.c"
    break;

  case 50:
#line 220 "syntax_analyzer.y"
                          { (yyval.expr) = new BinaryExpression((yyvsp[-2].expr), BinaryOp::LT, (yyvsp[0].expr)); }
#line 1986 "syntax_analyzer.tab.c"
    break;

  case 51:
#line 221 "syntax_analyzer.y"
                           { (yyval.expr) = new BinaryExpression((yyvsp[-2].expr), BinaryOp::LTE, (yyvsp[0].expr)); }
#line 1992 "syntax_analyzer.tab.c"
    break;

  case 52:
#line 224 "syntax_analyzer.y"
               { (yyval.expr) = (yyvsp[0].expr); }
#line 1998 "syntax_analyzer.tab.c"
    break;

  case 53:
#line 225 "syntax_analyzer.y"
                           { (yyval.expr) = new BinaryExpression((yyvsp[-2].expr), BinaryOp::ADD, (yyvsp[0].expr)); }
#line 2004 "syntax_analyzer.tab.c"
    break;

  case 54:
#line 226 "syntax_analyzer.y"
                           { (yyval.expr) = new BinaryExpression((yyvsp[-2].expr), BinaryOp::SUB, (yyvsp[0].expr)); }
#line 2010 "syntax_analyzer.tab.c"
    break;

  case 55:
#line 229 "syntax_analyzer.y"
                 { (yyval.expr) = (yyvsp[0].expr); }
#line 2016 "syntax_analyzer.tab.c"
    break;

  case 56:
#line 230 "syntax_analyzer.y"
                             { (yyval.expr) = new BinaryExpression((yyvsp[-2].expr), BinaryOp::MUL, (yyvsp[0].expr)); }
#line 2022 "syntax_analyzer.tab.c"
    break;

  case 57:
#line 231 "syntax_analyzer.y"
                             { (yyval.expr) = new BinaryExpression((yyvsp[-2].expr), BinaryOp::DIV, (yyvsp[0].expr)); }
#line 2028 "syntax_analyzer.tab.c"
    break;

  case 58:
#line 232 "syntax_analyzer.y"
                             { (yyval.expr) = new BinaryExpression((yyvsp[-2].expr), BinaryOp::MOD, (yyvsp[0].expr)); }
#line 2034 "syntax_analyzer.tab.c"
    break;

  case 59:
#line 235 "syntax_analyzer.y"
                     { (yyval.expr) = (yyvsp[0].expr); }
#line 2040 "syntax_analyzer.tab.c"
    break;

  case 60:
#line 236 "syntax_analyzer.y"
                                                 { 
            (yyval.expr) = new FuncCallExpression((yyvsp[-2].ident), nullptr); 
      }
#line 2048 "syntax_analyzer.tab.c"
    break;

  case 61:
#line 239 "syntax_analyzer.y"
                                                             { 
            (yyval.expr) = new FuncCallExpression((yyvsp[-3].ident), (yyvsp[-1].actual_args)); 
      }
#line 2056 "syntax_analyzer.tab.c"
    break;

  case 62:
#line 242 "syntax_analyzer.y"
                      { (yyval.expr) = new UnaryExpression(UnaryOp::POSITIVE, (yyvsp[0].expr)); }
#line 2062 "syntax_analyzer.tab.c"
    break;

  case 63:
#line 243 "syntax_analyzer.y"
                      { (yyval.expr) = new UnaryExpression(UnaryOp::NEGATIVE, (yyvsp[0].expr)); }
#line 2068 "syntax_analyzer.tab.c"
    break;

  case 64:
#line 244 "syntax_analyzer.y"
                      { (yyval.expr) = new UnaryExpression(UnaryOp::NOT, (yyvsp[0].expr)); }
#line 2074 "syntax_analyzer.tab.c"
    break;

  case 65:
#line 247 "syntax_analyzer.y"
                                                              { 
            (yyval.function_definition) = new FunctionDefinition((yyvsp[-4].type), (yyvsp[-3].ident), new FormalArgumentList(), (yyvsp[0].block));  
      }
#line 2082 "syntax_analyzer.tab.c"
    break;

  case 66:
#line 250 "syntax_analyzer.y"
                                                                         { 
            (yyval.function_definition) = new FunctionDefinition((yyvsp[-5].type), (yyvsp[-4].ident), (yyvsp[-2].formal_args), (yyvsp[0].block)); 
      }
#line 2090 "syntax_analyzer.tab.c"
    break;

  case 67:
#line 253 "syntax_analyzer.y"
                                                            { 
            (yyval.function_definition) = new FunctionDefinition(SysType::VOID, (yyvsp[-3].ident), new FormalArgumentList(), (yyvsp[0].block)); 
      }
#line 2098 "syntax_analyzer.tab.c"
    break;

  case 68:
#line 256 "syntax_analyzer.y"
                                                                        { 
            (yyval.function_definition) = new FunctionDefinition(SysType::VOID, (yyvsp[-4].ident), (yyvsp[-2].formal_args), (yyvsp[0].block)); 
      }
#line 2106 "syntax_analyzer.tab.c"
    break;

  case 69:
#line 261 "syntax_analyzer.y"
                        { 
            (yyval.formal_args) = new FormalArgumentList(); 
            (yyval.formal_args)->list_.emplace_back((yyvsp[0].formal_arg)); 
      }
#line 2115 "syntax_analyzer.tab.c"
    break;

  case 70:
#line 265 "syntax_analyzer.y"
                                     { 
            (yyval.formal_args) = (yyvsp[-2].formal_args);
            (yyval.formal_args)->list_.emplace_back((yyvsp[0].formal_arg)); 
      }
#line 2124 "syntax_analyzer.tab.c"
    break;

  case 71:
#line 271 "syntax_analyzer.y"
                        { (yyval.formal_arg) = new FormalArgument((yyvsp[-1].type), (yyvsp[0].ident)); }
#line 2130 "syntax_analyzer.tab.c"
    break;

  case 73:
#line 275 "syntax_analyzer.y"
                                                          {
            (yyval.formal_arg) = new FormalArgument((yyvsp[-3].type), (yyvsp[-2].ident));
            (yyval.formal_arg)->identifier_->dimension_.emplace_back(nullptr);
      }
#line 2139 "syntax_analyzer.tab.c"
    break;

  case 74:
#line 279 "syntax_analyzer.y"
                                                            { 
            (yyval.formal_arg) = (yyvsp[-3].formal_arg);
            (yyval.formal_arg)->identifier_->dimension_.emplace_back((yyvsp[-1].expr));
      }
#line 2148 "syntax_analyzer.tab.c"
    break;

  case 75:
#line 285 "syntax_analyzer.y"
                    { (yyval.actual_args) = new ActualArgumentList(); (yyval.actual_args)->list_.emplace_back((yyvsp[0].expr)); }
#line 2154 "syntax_analyzer.tab.c"
    break;

  case 76:
#line 286 "syntax_analyzer.y"
                                 { (yyval.actual_args) = (yyvsp[-2].actual_args); (yyval.actual_args)->list_.emplace_back((yyvsp[0].expr)); }
#line 2160 "syntax_analyzer.tab.c"
    break;

  case 77:
#line 289 "syntax_analyzer.y"
                                { (yyval.block) = new Block();
            if((yyval.block)->scope_ == nullptr) (yyval.block)->scope_ = new Scope();
      }
#line 2168 "syntax_analyzer.tab.c"
    break;

  case 78:
#line 292 "syntax_analyzer.y"
                                           { 
            (yyval.block) = (yyvsp[-1].block); 
            if((yyval.block)->scope_ == nullptr) (yyval.block)->scope_ = new Scope();
            for(auto&stmt : (yyvsp[-1].block)->statements_) {
                if (stmt){
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
            }
      }
#line 2193 "syntax_analyzer.tab.c"
    break;

  case 79:
#line 314 "syntax_analyzer.y"
                      { 
            (yyval.block) = new Block(); 
            if ((yyvsp[0].stmt) != nullptr) (yyval.block)->statements_.emplace_back((yyvsp[0].stmt)); 
      }
#line 2202 "syntax_analyzer.tab.c"
    break;

  case 80:
#line 318 "syntax_analyzer.y"
                             { 
            (yyval.block) = (yyvsp[-1].block); 
            if ((yyvsp[-1].block) != nullptr) (yyval.block)->statements_.emplace_back((yyvsp[0].stmt)); 
      }
#line 2211 "syntax_analyzer.tab.c"
    break;

  case 81:
#line 324 "syntax_analyzer.y"
                { (yyval.stmt) = (yyvsp[0].declare_statement); }
#line 2217 "syntax_analyzer.tab.c"
    break;

  case 82:
#line 325 "syntax_analyzer.y"
             { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2223 "syntax_analyzer.tab.c"
    break;

  case 83:
#line 328 "syntax_analyzer.y"
                                   { (yyval.stmt) = new AssignStatement((yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 2229 "syntax_analyzer.tab.c"
    break;

  case 84:
#line 329 "syntax_analyzer.y"
                  { (yyval.stmt) = nullptr; }
#line 2235 "syntax_analyzer.tab.c"
    break;

  case 85:
#line 330 "syntax_analyzer.y"
                         { (yyval.stmt) = new EvalStatement((yyvsp[-1].expr)); }
#line 2241 "syntax_analyzer.tab.c"
    break;

  case 86:
#line 331 "syntax_analyzer.y"
              { (yyval.stmt) = (yyvsp[0].block); }
#line 2247 "syntax_analyzer.tab.c"
    break;

  case 87:
#line 332 "syntax_analyzer.y"
                                                          { 
            (yyval.stmt) = new IfElseStatement((yyvsp[-2].expr), (yyvsp[0].stmt), nullptr);
            if ((yyvsp[0].stmt)) {
              if ((yyvsp[0].stmt)->statement_type() == StmtType::BLOCK)
              dynamic_cast<Block*>((yyvsp[0].stmt))->scope_->parent = dynamic_cast<IfElseStatement*>((yyval.stmt))->scope_;   
              else if ((yyvsp[0].stmt)->statement_type() == StmtType::IFELSE)
              dynamic_cast<IfElseStatement*>((yyvsp[0].stmt))->scope_->parent = dynamic_cast<IfElseStatement*>((yyval.stmt))->scope_;   
              else if ((yyvsp[0].stmt)->statement_type() == StmtType::WHILE)
              dynamic_cast<WhileStatement*>((yyvsp[0].stmt))->scope_->parent = dynamic_cast<IfElseStatement*>((yyval.stmt))->scope_;   
            }
      }
#line 2263 "syntax_analyzer.tab.c"
    break;

  case 88:
#line 343 "syntax_analyzer.y"
                                                                    { 
            (yyval.stmt) = new IfElseStatement((yyvsp[-4].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt)); 
            if ((yyvsp[-2].stmt)) {
              if ((yyvsp[-2].stmt)->statement_type() == StmtType::BLOCK)
                 dynamic_cast<Block*>((yyvsp[-2].stmt))->scope_->parent = dynamic_cast<IfElseStatement*>((yyval.stmt))->scope_;   
              else if ((yyvsp[-2].stmt)->statement_type() == StmtType::IFELSE)
                 dynamic_cast<IfElseStatement*>((yyvsp[-2].stmt))->scope_->parent = dynamic_cast<IfElseStatement*>((yyval.stmt))->scope_;   
              else if ((yyvsp[-2].stmt)->statement_type() == StmtType::WHILE)
                 dynamic_cast<WhileStatement*>((yyvsp[-2].stmt))->scope_->parent = dynamic_cast<IfElseStatement*>((yyval.stmt))->scope_;   
            }
            if ((yyvsp[0].stmt)) {
              if ((yyvsp[0].stmt)->statement_type() == StmtType::BLOCK)
                 dynamic_cast<Block*>((yyvsp[0].stmt))->scope_->parent = dynamic_cast<IfElseStatement*>((yyval.stmt))->scope_;   
              else if ((yyvsp[0].stmt)->statement_type() == StmtType::IFELSE)
                 dynamic_cast<IfElseStatement*>((yyvsp[0].stmt))->scope_->parent = dynamic_cast<IfElseStatement*>((yyval.stmt))->scope_;   
              else if ((yyvsp[0].stmt)->statement_type() == StmtType::WHILE)
                 dynamic_cast<WhileStatement*>((yyvsp[0].stmt))->scope_->parent = dynamic_cast<IfElseStatement*>((yyval.stmt))->scope_;   
            }
      }
#line 2287 "syntax_analyzer.tab.c"
    break;

  case 89:
#line 362 "syntax_analyzer.y"
                                                             { 
            (yyval.stmt) = new WhileStatement((yyvsp[-2].expr), (yyvsp[0].stmt)); 
            if ((yyvsp[0].stmt)) {
              if ((yyvsp[0].stmt)->statement_type() == StmtType::BLOCK)
                 dynamic_cast<Block*>((yyvsp[0].stmt))->scope_->parent = dynamic_cast<WhileStatement*>((yyval.stmt))->scope_;   
              else if ((yyvsp[0].stmt)->statement_type() == StmtType::IFELSE)
                 dynamic_cast<IfElseStatement*>((yyvsp[0].stmt))->scope_->parent = dynamic_cast<WhileStatement*>((yyval.stmt))->scope_;   
              else if ((yyvsp[0].stmt)->statement_type() == StmtType::WHILE)
                 dynamic_cast<WhileStatement*>((yyvsp[0].stmt))->scope_->parent = dynamic_cast<WhileStatement*>((yyval.stmt))->scope_;   
            }
      }
#line 2303 "syntax_analyzer.tab.c"
    break;

  case 90:
#line 373 "syntax_analyzer.y"
                        { (yyval.stmt) = new BreakStatement(); }
#line 2309 "syntax_analyzer.tab.c"
    break;

  case 91:
#line 374 "syntax_analyzer.y"
                           { (yyval.stmt) = new ContinueStatement(); }
#line 2315 "syntax_analyzer.tab.c"
    break;

  case 92:
#line 375 "syntax_analyzer.y"
                         { (yyval.stmt) = new ReturnStatement(); }
#line 2321 "syntax_analyzer.tab.c"
    break;

  case 93:
#line 376 "syntax_analyzer.y"
                                { (yyval.stmt) = new ReturnStatement((yyvsp[-1].expr)); }
#line 2327 "syntax_analyzer.tab.c"
    break;


#line 2331 "syntax_analyzer.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
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
  return yyresult;
}
#line 379 "syntax_analyzer.y"


extern "C" void yyerror(const char *s) {
      fprintf(stderr, "%d:%d: error: %s\n", yylloc.first_line,
              yylloc.first_column, s);
}

