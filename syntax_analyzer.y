%{
#include <iostream>
#include <cstdlib>
#include "ast.h"
ASTRoot* root = nullptr;

extern int yylex();
void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
}
#define YYERROR_VERBOSE true
#ifdef YYDEBUG
#undef YYDEBUG
#endif
#define YYDEBUG 1
#define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do {                                                              \
        if (N) {                                                      \
            (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;    \
            (Current).first_column = YYRHSLOC (Rhs, 1).first_column;  \
            (Current).last_line    = YYRHSLOC (Rhs, N).last_line;     \
            (Current).last_column  = YYRHSLOC (Rhs, N).last_column;   \
        } else {                                                      \
            (Current).first_line   = (Current).last_line   =          \
              YYRHSLOC (Rhs, 0).last_line;                            \
            (Current).first_column = (Current).last_column =          \
              YYRHSLOC (Rhs, 0).last_column;                          \
        }                                                             \
        yylloc = Current;                                             \
    } while (0)
%}

%locations
%union {
      SysType type;
      int token;
      float f_val;
      ASTRoot * root;
      ASTDeclareStatement* declare_statement;
      ASTDeclare* declare;
      ASTExpression* expr;
      ASTStatement* stmt;

      ArrayDeclare* array_declare;

      Identifier* Ident;
      FunctionDefinition* funcdef;
      ArrayDeclareInitValue* array_init_value;
      ArrayIdentifier* array_identifier;
      FunctionCallArgList* arg_list;
      ArgumentList* fundefarglist;
      Argument* fundefarg;
      Block* block;
      AssignStatement* assignmentstmt;
      IfElseStatement* ifelsestmt;
      ASTCondExpression* condexp;
      std::string *string;
}

%token <token> ADD SUB MUL DIV MOD
%token <token> ASSIGN EQ NEQ LT LTE GT GTE
%token <token> AND OR NOT
%token <token> IF ELSE WHILE BREAK CONTINUE RETURN
%token <token> CONST INT VOID FLOAT
%token <token> LEFT_PARENTHESES RIGHT_PARENTHESES 
%token <token> LEFT_BRACKETS RIGHT_BRACKETS 
%token <token> LEFT_BRACES RIGHT_BRACES 
%token <token> COMMA SEMICOLON

%token <string> IDENTIFIER 
%token <f_val> FLOATPOINT
%token <token> INTEGER 

%left COMMA
%left ASSIGN
%left EQ NEQ LT LTE GT GTE
%left ADD SUB
%left MUL DIV MOD
%left NOT

%type <root> CompUnit
%type <type> BType
%type <declare_statement> Decl ConstDecl VarDecl
%type <declare> VarDef ConstDef
%type <array_declare> ArrayDef
%type <funcdef> FuncDef

%type <Ident> Ident LVal ArrayIdent
%type <expr> Number Exp LOrExp LAndExp EqExp AddExp MulExp PrimaryExp RelExp UnaryExp
%type <array_identifier> ArrayItem
%type <fundefarglist> FuncFParams
%type <fundefarg> FuncFParam FuncFParamArray FuncFParamOne
%type <array_init_value> InitValArray InitValArrayInner
%type <arg_list> FuncRParams
%type <block> Block BlockItems
%type <stmt> BlockItem Stmt
%type <condexp> Cond

%start CompUnit

%%

CompUnit: CompUnit Decl { $$ = $1; $$->decls.emplace_back($2); std::cout << root->decls.size() << std::endl;}
      | CompUnit FuncDef { $$ = $1; $$->func_defs.emplace_back($2); }
      | Decl { root = new ASTRoot(); $$ = root; $$->decls.emplace_back($1); }
      | FuncDef { root = new ASTRoot(); $$ = root; $$->func_defs.emplace_back($1); }
      ;

Decl: ConstDecl SEMICOLON { $$ = $1;}
    | VarDecl SEMICOLON { $$ = $1; }
    ;

BType: INT { $$ = SysType::INT; }
    | FLOAT { $$ = SysType::FLOAT; }
    ;

ConstDecl: CONST BType ConstDef { $$ = new ASTDeclareStatement($2); $$->defs.emplace_back($3); }
      | ConstDecl COMMA ConstDef { $$ = $1; $$->defs.emplace_back($3); }
      ;

ConstDef: Ident ASSIGN AddExp { $$ = new VarDeclare($1, $3, true); }
      | ArrayIdent ASSIGN InitValArray { $$ = new ArrayDeclare($1, $3, true); }
      ;

ArrayIdent: Ident LEFT_BRACKETS Exp RIGHT_BRACKETS { $$ = $1; $$->dimension.emplace_back($2); }
      | ArrayIdent LEFT_BRACKETS Exp RIGHT_BRACKETS { $$ = $1; $$->dimension.emplace_back($3); }
      ;

ArrayDef: LEFT_BRACKETS Exp RIGHT_BRACKETS { $$ = new ArrayDeclare(); $$->shape.emplace_back($2); }
      | ArrayDef LEFT_BRACKETS Exp RIGHT_BRACKETS { $$ = $1; $$->shape.emplace_back($3); }
      ;

VarDecl: BType VarDef { $$ = new ASTDeclareStatement($1); $$->defs.emplace_back($2); }
      | VarDecl COMMA VarDef { $$ = $1; $$->defs.emplace_back($3); }
      ;

VarDef: Ident { $$ = new VarDeclare(*$1, nullptr, false); }
      | Ident ASSIGN AddExp { $$ = new VarDeclare(*$1, $3, false); }
      | Ident ArrayDef { $$ = $2; dynamic_cast<ArrayDeclare*>($$)->id = *$1; }
      | Ident ArrayDef ASSIGN InitValArray { $$ = $2; dynamic_cast<ArrayDeclare*>($$)->id = *$1; dynamic_cast<ArrayDeclare*>($$)->value = $4; }
      ;

InitValArray: LEFT_BRACES RIGHT_BRACES { $$ = new ArrayDeclareInitValue(false, nullptr); }
      | LEFT_BRACES InitValArrayInner RIGHT_BRACES { $$ = $2; }
      ;

InitValArrayInner: 
      InitValArrayInner COMMA InitValArray { $$ = $1; $$->value_list.push_back($3); }
      | InitValArrayInner COMMA AddExp { $$ = $1; $$->value_list.push_back(new ArrayDeclareInitValue(true, $3)); }
      | InitValArray { $$ = new ArrayDeclareInitValue(false, nullptr); $$->value_list.push_back($1); }
      | AddExp { $$ = new ArrayDeclareInitValue(false, nullptr); $$->value_list.push_back(new ArrayDeclareInitValue(true, $1)); }
      | AddExp COMMA InitValArray  {
            $$ = new ArrayDeclareInitValue(false, nullptr);
            $$->value_list.push_back(new ArrayDeclareInitValue(true, $1));
            $$->value_list.push_back($3);
      }
      ;

Exp: AddExp { $$ = $1; }
   ;


LOrExp: LAndExp { $$ = $1; }
      | LOrExp OR LAndExp { $$ = new ASTBinaryExpression($1, BinaryOp::OR, $3); }
      ;

LAndExp: EqExp { $$ = $1; }
      | LAndExp AND EqExp  { $$ = new ASTBinaryExpression($1, BinaryOp::AND, $3); }
      ;

EqExp: RelExp { $$ = $1; }
     | EqExp EQ RelExp  { $$ = new ASTBinaryExpression($1, BinaryOp::EQ, $3); }
     | EqExp NEQ RelExp  { $$ = new ASTBinaryExpression($1, BinaryOp::NEQ, $3); }
     ;

RelExp: AddExp { $$ = $1; }
      | RelExp GT AddExp  { $$ = new ASTBinaryExpression($1, BinaryOp::GT, $3); }
      | RelExp GTE AddExp  { $$ = new ASTBinaryExpression($1, BinaryOp::GTE, $3); }
      | RelExp LT AddExp  { $$ = new ASTBinaryExpression($1, BinaryOp::LT, $3); }
      | RelExp LTE AddExp  { $$ = new ASTBinaryExpression($1, BinaryOp::LTE, $3); }
      ;

AddExp: MulExp { $$ = $1; }
      | AddExp ADD MulExp  { $$ = new ASTBinaryExpression($1, BinaryOp::ADD, $3); }
      | AddExp SUB MulExp  { $$ = new ASTBinaryExpression($1, BinaryOp::SUB, $3); }    
      ;

MulExp: UnaryExp { $$ = $1; }
      | MulExp MUL UnaryExp  { $$ = new ASTBinaryExpression($1, BinaryOp::MUL, $3); }
      | MulExp DIV UnaryExp  { $$ = new ASTBinaryExpression($1, BinaryOp::DIV, $3); }
      | MulExp MOD UnaryExp  { $$ = new ASTBinaryExpression($1, BinaryOp::MOD, $3); }
      ;

UnaryExp: PrimaryExp { $$ = $1; }
      | Ident LEFT_PARENTHESES RIGHT_PARENTHESES { $$ = new FunctionCall(*$1, *(new FunctionCallArgList())); }
      | Ident LEFT_PARENTHESES FuncRParams RIGHT_PARENTHESES { $$ = new FunctionCall(*$1, *$3); };
      | ADD UnaryExp  { $$ = new ASTUnaryExpression(UnaryOp::POSITIVE, $2); }
      | SUB UnaryExp  { $$ = new ASTUnaryExpression(UnaryOp::NEGATIVE, $2); }
      | NOT UnaryExp  { $$ = new ASTUnaryExpression(UnaryOp::NOT, $2); }
      ;

PrimaryExp: LEFT_PARENTHESES Cond RIGHT_PARENTHESES { $$ = $2; }
      | LVal {  }
      | Number { $$ = $1; }
      | LVal ASSIGN AddExp { $$ = new AssignStatement(*$1, *$3); }
      ;

ArrayItem: LVal LEFT_BRACKETS Exp RIGHT_BRACKETS { $$ = new ArrayIdentifier(*$1); $$->shape.push_back($3);}
      | ArrayItem LEFT_BRACKETS Exp RIGHT_BRACKETS { $$ = $1; $$->shape.push_back($3);}
      ;

LVal: Ident
      | ArrayItem
      ;

FuncDef: BType IDENTIFIER LEFT_PARENTHESES RIGHT_PARENTHESES Block { $$ = new FunctionDefinition($1, *$2, nullptr, $5); }
      | BType IDENTIFIER LEFT_PARENTHESES FuncFParams RIGHT_PARENTHESES Block { $$ = new FunctionDefinition($1, *$2, $4, $6); }
      | VOID IDENTIFIER LEFT_PARENTHESES RIGHT_PARENTHESES Block { $$ = new FunctionDefinition(SysType::VOID, *$2, nullptr, $5); }
      | VOID IDENTIFIER LEFT_PARENTHESES FuncFParams RIGHT_PARENTHESES Block { $$ = new FunctionDefinition(SysType::VOID, *$2, $4, $6); }
      ;

FuncFParams: FuncFParam { $$ = new ArgumentList(); $$->list.emplace_back($1); }
      | FuncFParams COMMA FuncFParam { $$->list.emplace_back($3); }
      ;

FuncFParam: BType IDENTIFIER { $$ = new Argument($1, *$2); }
      | FuncFParamArray
      ;

FuncRParams: FuncRParams COMMA AddExp { $$ = $1; $$->args.push_back($3); }
           | AddExp { $$ = new FunctionCallArgList(); $$->args.push_back($1); }
           ;

FuncFParamOne: BType Ident { $$ = new FunctionDefineArg($1, *$2); };

FuncFParamArray: FuncFParamOne LEFT_BRACKETS RIGHT_BRACKETS {
      $$ = new FunctionDefineArg($1->type, *new ArrayIdentifier(*(new ArrayIdentifier($1->name))));
      ((ArrayIdentifier*)&($$->name))->shape.push_back(new ASTNumber(SysType::INT,1));
      delete $1;
      }
      | FuncFParamArray LEFT_BRACKETS Exp RIGHT_BRACKETS { $$ = $1; ((ArrayIdentifier*)&($$->name))->shape.push_back($3);; }
      ;

Block: LEFT_BRACES RIGHT_BRACES { $$ = new Block(); }
     | LEFT_BRACES BlockItems RIGHT_BRACES { $$ = $2; }
     ;

BlockItems: BlockItem { $$ = new Block(); $$->statements.push_back($1); }
          | BlockItems BlockItem { $$ = $1; $$->statements.push_back($2); }
          ;

BlockItem: Decl { $$ = $1; }
         | Stmt { $$ = $1; }
         ;

Stmt: LVal ASSIGN AddExp SEMICOLON { $$ = new AssignStatement(*$1, *$3); }
      | SEMICOLON { $$ = new VoidStatement(); }
      | Exp SEMICOLON { $$ = new  EvalStatement(*$1); }
      | Block { $$ = $1; }
      | IF LEFT_PARENTHESES Cond RIGHT_PARENTHESES Stmt { $$ = new IfElseStatement(*$3, *$5, *new VoidStatement()); }
      | IF LEFT_PARENTHESES Cond RIGHT_PARENTHESES Stmt ELSE Stmt { $$ = new IfElseStatement(*$3, *$5, *$7); }
      | WHILE LEFT_PARENTHESES Cond RIGHT_PARENTHESES Stmt { $$ = new WhileStatement(*$3, *$5);}
      | BREAK SEMICOLON { $$ = new BreakStatement(); }
      | CONTINUE SEMICOLON { $$ = new ContinueStatement(); }
      | RETURN Exp SEMICOLON { $$ = new ReturnStatement($2); }
      | RETURN SEMICOLON { $$ = new ReturnStatement(); }
      ;

Cond: LOrExp {  }
      ;

Number: INTEGER { $$ = new ASTNumber(SysType::INT, $1); }
      | FLOATPOINT { $$ = new ASTNumber(SysType::FLOAT, $1); }
      ;
Ident: IDENTIFIER { $$ = new Identifier(*$1); }
      ;