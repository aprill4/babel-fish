%{
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

%}

%locations

%union {
      SysType type;
      std::string *string;
      int token;
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
%token <token> INTEGER
%token <f_val> FLOATPOINT

%type <root> CompUnit
%type <type> BType
%type <declare_statement> Decl ConstDecl VarDecl
%type <function_definition> FuncDef
%type <declare> VarDef ConstDef
%type <ident> Ident ArrayIdent
%type <array_val> ArrayVal ArrayVals
%type <expr> LVal ArrayItem Number LOrExp LAndExp EqExp AddExp MulExp PrimaryExp RelExp UnaryExp
%type <formal_args> FuncFParams
%type <formal_arg> FuncFParam FuncFParamArray
%type <actual_args> FuncRParams
%type <block> Block BlockItems
%type <stmt> BlockItem Stmt

%start CompUnit

%%

CompUnit: CompUnit Decl { 
            $$ = $1; 
            $$->decls.emplace_back($2); 
      }
      | CompUnit FuncDef { 
            $$ = $1; 
            $$->func_defs.emplace_back($2); 
      }
      | Decl { root = new Root(); $$ = root; $$->decls.emplace_back($1); }
      | FuncDef { root = new Root(); $$ = root; $$->func_defs.emplace_back($1); }
      ;

Decl: ConstDecl SEMICOLON { $$ = $1;}
    | VarDecl SEMICOLON { $$ = $1; }
    ;

BType: INT { $$ = SysType::INT; }
    | FLOAT { $$ = SysType::FLOAT; }
    ;

ConstDecl: CONST BType ConstDef { $$ = new DeclareStatement($2); $$->defs.emplace_back($3); }
      | ConstDecl COMMA ConstDef { $$ = $1; $$->defs.emplace_back($3); }
      ;

ConstDef: Ident ASSIGN AddExp { $$ = new VarDeclare($1, $3, true); }
      | ArrayIdent ASSIGN ArrayVal { $$ = new ArrayDeclare($1, $3, true); }
      ;

VarDecl: BType VarDef { $$ = new DeclareStatement($1); $$->defs.emplace_back($2); }
      | VarDecl COMMA VarDef { $$ = $1; $$->defs.emplace_back($3); }
      ;

VarDef: Ident { $$ = new VarDeclare($1, nullptr, false); }
      | Ident ASSIGN AddExp { $$ = new VarDeclare($1, $3, false); }
      | ArrayIdent { $$ = new ArrayDeclare($1, nullptr, false); }
      | ArrayIdent ASSIGN ArrayVal { $$ = new ArrayDeclare($1, $3, false); }
      ;

ArrayIdent: Ident LEFT_BRACKETS AddExp RIGHT_BRACKETS { $$ = $1; $$->dimension.emplace_back($3); }
      | ArrayIdent LEFT_BRACKETS AddExp RIGHT_BRACKETS { $$ = $1; $$->dimension.emplace_back($3); }
      ;

ArrayVal: LEFT_BRACES RIGHT_BRACES { $$ = new ArrayValue(false, nullptr); }
      | LEFT_BRACES ArrayVals RIGHT_BRACES { $$ = $2; }

ArrayVals: AddExp  { 
            $$ = new ArrayValue(false, nullptr); 
            $$->value_list.emplace_back(new ArrayValue(true, $1)); 
      }
      | ArrayVal {
            $$ = new ArrayValue(false, nullptr);
            $$->value_list.emplace_back($1); 
      }
      | ArrayVals COMMA AddExp {
            $$ = $1;
            $$->value_list.emplace_back(new ArrayValue(true, $3));
      }
      | ArrayVals COMMA ArrayVal {
            $$ = $1;
            $$->value_list.emplace_back($3);
      }

Number: INTEGER { $$ = new Number(SysType::INT, $1); }
      | FLOATPOINT { $$ = new Number(SysType::FLOAT, $1); }
      ;

Ident: IDENTIFIER { $$ = new Identifier($1); }
      ;

LVal: Ident { $$ = new LValExpression($1); }
      | ArrayItem { $$ = $1; }
      ;

ArrayItem: Ident LEFT_BRACKETS AddExp RIGHT_BRACKETS { 
            $$ = new LValExpression($1);
            dynamic_cast<LValExpression*>($$)->identifier->dimension.emplace_back($3);
      }
      | ArrayItem LEFT_BRACKETS AddExp RIGHT_BRACKETS { 
            $$ = $1;
            dynamic_cast<LValExpression*>($$)->identifier->dimension.emplace_back($3);
      }
      ;

PrimaryExp: LEFT_PARENTHESES AddExp RIGHT_PARENTHESES { $$ = $2; }
      | LVal { $$ = $1; }
      | Number { $$ = $1; }
      ;

LOrExp: LAndExp { $$ = $1; }
      | LOrExp OR LAndExp { $$ = new BinaryExpression($1, BinaryOp::OR, $3); }
      ;

LAndExp: EqExp { $$ = $1; }
      | LAndExp AND EqExp  { $$ = new BinaryExpression($1, BinaryOp::AND, $3); }
      ;

EqExp: RelExp { $$ = $1; }
     | EqExp EQ RelExp  { $$ = new BinaryExpression($1, BinaryOp::EQ, $3); }
     | EqExp NEQ RelExp  { $$ = new BinaryExpression($1, BinaryOp::NEQ, $3); }
     ;

RelExp: AddExp { $$ = $1; }
      | RelExp GT AddExp  { $$ = new BinaryExpression($1, BinaryOp::GT, $3); }
      | RelExp GTE AddExp  { $$ = new BinaryExpression($1, BinaryOp::GTE, $3); }
      | RelExp LT AddExp  { $$ = new BinaryExpression($1, BinaryOp::LT, $3); }
      | RelExp LTE AddExp  { $$ = new BinaryExpression($1, BinaryOp::LTE, $3); }
      ;

AddExp: MulExp { $$ = $1; }
      | AddExp ADD MulExp  { $$ = new BinaryExpression($1, BinaryOp::ADD, $3); }
      | AddExp SUB MulExp  { $$ = new BinaryExpression($1, BinaryOp::SUB, $3); }    
      ;

MulExp: UnaryExp { $$ = $1; }
      | MulExp MUL UnaryExp  { $$ = new BinaryExpression($1, BinaryOp::MUL, $3); }
      | MulExp DIV UnaryExp  { $$ = new BinaryExpression($1, BinaryOp::DIV, $3); }
      | MulExp MOD UnaryExp  { $$ = new BinaryExpression($1, BinaryOp::MOD, $3); }
      ;

UnaryExp: PrimaryExp { $$ = $1; }
      | Ident LEFT_PARENTHESES RIGHT_PARENTHESES { 
            $$ = new FuncCallExpression($1, nullptr); 
      }
      | Ident LEFT_PARENTHESES FuncRParams RIGHT_PARENTHESES { 
            $$ = new FuncCallExpression($1, $3); 
      }
      | ADD UnaryExp  { $$ = new UnaryExpression(UnaryOp::POSITIVE, $2); }
      | SUB UnaryExp  { $$ = new UnaryExpression(UnaryOp::NEGATIVE, $2); }
      | NOT UnaryExp  { $$ = new UnaryExpression(UnaryOp::NOT, $2); }
      ;

FuncDef: BType Ident LEFT_PARENTHESES RIGHT_PARENTHESES Block { 
            $$ = new FunctionDefinition($1, $2, nullptr, $5); 
      }
      | BType Ident LEFT_PARENTHESES FuncFParams RIGHT_PARENTHESES Block { 
            $$ = new FunctionDefinition($1, $2, $4, $6); 
      }
      | VOID Ident LEFT_PARENTHESES RIGHT_PARENTHESES Block { 
            $$ = new FunctionDefinition(SysType::VOID, $2, nullptr, $5); 
      }
      | VOID Ident LEFT_PARENTHESES FuncFParams RIGHT_PARENTHESES Block { 
            $$ = new FunctionDefinition(SysType::VOID, $2, $4, $6); 
      }
      ;

FuncFParams: FuncFParam { 
            $$ = new FormalArgumentList(); 
            $$->list.emplace_back($1); 
      }
      | FuncFParams COMMA FuncFParam { 
            $$->list.emplace_back($3); 
      }
      ;

FuncFParam: BType Ident { $$ = new FormalArgument($1, $2); }
      | FuncFParamArray
      ;

FuncFParamArray: BType Ident LEFT_BRACKETS RIGHT_BRACKETS {
            $$ = new FormalArgument($1, $2);
            $$->identifier->dimension.emplace_back(nullptr);
      }
      | FuncFParamArray LEFT_BRACKETS AddExp RIGHT_BRACKETS { 
            $$ = $1;
            $$->identifier->dimension.emplace_back($3);
      }
      ;

FuncRParams: AddExp { $$ = new ActualArgumentList(); $$->list.emplace_back($1); }
      | FuncRParams COMMA AddExp { $$ = $1; $$->list.emplace_back($3); }
      ;

Block: LEFT_BRACES RIGHT_BRACES { $$ = new Block(); }
     | LEFT_BRACES BlockItems RIGHT_BRACES { $$ = $2; }
     ;

BlockItems: BlockItem { 
            $$ = new Block(); 
            if ($1 != nullptr)
                  $$->statements.emplace_back($1); 
      }
      | BlockItems BlockItem { 
            $$ = $1; 
            if ($1 != nullptr)
                  $$->statements.emplace_back($2); 
      }
      ;

BlockItem: Decl { $$ = $1; }
      | Stmt { $$ = $1; }
      ;

Stmt: LVal ASSIGN AddExp SEMICOLON { $$ = new AssignStatement($1, $3); }
      | SEMICOLON { $$ = nullptr; }
      | AddExp SEMICOLON { $$ = new EvalStatement($1); }
      | Block { $$ = $1; }
      | IF LEFT_PARENTHESES LOrExp RIGHT_PARENTHESES Stmt { $$ = new IfElseStatement($3, $5, nullptr); }
      | IF LEFT_PARENTHESES LOrExp RIGHT_PARENTHESES Stmt ELSE Stmt { $$ = new IfElseStatement($3, $5, $7); }
      | WHILE LEFT_PARENTHESES LOrExp RIGHT_PARENTHESES Stmt { $$ = new WhileStatement($3, $5);}
      | BREAK SEMICOLON { $$ = new BreakStatement(); }
      | CONTINUE SEMICOLON { $$ = new ContinueStatement(); }
      | RETURN SEMICOLON { $$ = new ReturnStatement(); }
      | RETURN AddExp SEMICOLON { $$ = new ReturnStatement($2); }
      ;