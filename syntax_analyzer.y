%{
#include <iostream>
#include <cstdlib>
#include "ast.h"
Root* root = nullptr;

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
      Root * root;
      DeclareStatement* declare_statement;
      Declare* declare;
      Expression* expr;
      Statement* stmt;

      Identifier* Ident;
      FunctionDefinition* funcdef;
      ArrayDeclareInitValue* array_init_value;
      // ArrayIdentifier* array_identifier;
      FunctionCallArgList* arg_list;
      ArgumentList* fundefarglist;
      Argument* fundefarg;
      Block* block;
      AssignStatement* assignmentstmt;
      IfElseStatement* ifelsestmt;
      CondExpression* condexp;
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
%type <funcdef> FuncDef

%type <Ident> Ident LVal ArrayIdent ArrayItem
%type <expr> Number Exp LOrExp LAndExp EqExp AddExp MulExp PrimaryExp RelExp UnaryExp CommaExpr 
/* %type <array_identifier> ArrayItem */
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
      | ArrayIdent ASSIGN InitValArray { $$ = new ArrayDeclare($1, $3, true); }
      ;

VarDecl: BType VarDef { $$ = new DeclareStatement($1); $$->defs.emplace_back($2); }
      | VarDecl COMMA VarDef { $$ = $1; $$->defs.emplace_back($3); }
      ;

VarDef: Ident { $$ = new VarDeclare($1, nullptr, false); }
      | Ident ASSIGN AddExp { $$ = new VarDeclare($1, $3, false); }
      | ArrayIdent { $$ = new ArrayDeclare($1, nullptr, false); }
      | ArrayIdent ASSIGN InitValArray { $$ = new ArrayDeclare($1, $3, false); }
      ;

ArrayIdent: Ident LEFT_BRACKETS Exp RIGHT_BRACKETS { 
            // $$ = $1; $$->dimension.emplace_back($2); 
      }
      | ArrayIdent LEFT_BRACKETS Exp RIGHT_BRACKETS { 
            // $$ = $1; $$->dimension.emplace_back($3); 
      }
      ;

InitValArray: LEFT_BRACES RIGHT_BRACES { $$ = new ArrayDeclareInitValue(false, nullptr); }
      | LEFT_BRACES InitValArrayInner RIGHT_BRACES { $$ = $2; }
      ;

InitValArrayInner: InitValArrayInner COMMA InitValArray {
            //  $$ = $1; $$->value_list.push_back($3); 
      }
      | InitValArrayInner COMMA AddExp { 
            // $$ = $1; $$->value_list.push_back(ArrayDeclareInitValue(true, $3)); 
      }
      | InitValArray { 
            // $$ = new ArrayDeclareInitValue(false, nullptr); $$->value_list.push_back($1); 
      }
      | AddExp { 
            // $$ = new ArrayDeclareInitValue(false, nullptr); $$->value_list.push_back(new ArrayDeclareInitValue(true, $1)); 
      }
      | AddExp COMMA InitValArray  {
            // $$ = new ArrayDeclareInitValue(false, nullptr);
            // $$->value_list.push_back(new ArrayDeclareInitValue(true, $1));
            // $$->value_list.push_back($3);
      }
      | CommaExpr {
            // $$ = new ArrayDeclareInitValue(false, nullptr);
            // for (auto i : dynamic_cast<CommaExpression*>($1)->values) {
                  // $$->value_list.push_back(new ArrayDeclareInitValue(true, i));
            // }
            // delete $1;
      }
      | CommaExpr COMMA InitValArray {
            // $$ = new ArrayDeclareInitValue(false, nullptr);
            // for (auto i : dynamic_cast<CommaExpression*>($1)->values) {
                  // $$->value_list.push_back(new ArrayDeclareInitValue(true, i));
            // }
            // $$->value_list.push_back($3);
            // delete $1;
      }
      ;

Exp: AddExp
   | CommaExpr
   ;

CommaExpr: AddExp COMMA AddExp {
            //    auto n = new CommaExpression();
            //    n->values.push_back($1);
            //    n->values.push_back($3);
            //    $$ = n;
            }
         | CommaExpr COMMA AddExp {
            //    dynamic_cast<CommaExpression*>($1)->values.push_back($3);
            //    $$ = $1;
            }
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
            // $$ = new FunctionCall(*$1, *(new FunctionCallArgList())); 
      }
      | Ident LEFT_PARENTHESES FuncRParams RIGHT_PARENTHESES { 
            // $$ = new FunctionCall(*$1, *$3); 
      }
      | ADD UnaryExp  { $$ = new UnaryExpression(UnaryOp::POSITIVE, $2); }
      | SUB UnaryExp  { $$ = new UnaryExpression(UnaryOp::NEGATIVE, $2); }
      | NOT UnaryExp  { $$ = new UnaryExpression(UnaryOp::NOT, $2); }
      ;

PrimaryExp: LEFT_PARENTHESES Cond RIGHT_PARENTHESES { $$ = $2; }
      | LVal {  }
      | Number { $$ = $1; }
      | LVal ASSIGN AddExp { 
            // $$ = new AssignStatement(*$1, *$3); 
      }
      ;

ArrayItem: LVal LEFT_BRACKETS Exp RIGHT_BRACKETS { 
            // $$ = new Identifier(*$1); $$->dimension.emplace_back($3);
      }
      | ArrayItem LEFT_BRACKETS Exp RIGHT_BRACKETS { 
            // $$ = $1; $$->dimension.emplace_back($3);
      }
      ;

LVal: Ident
      | ArrayItem
      ;

FuncDef: BType Ident LEFT_PARENTHESES RIGHT_PARENTHESES Block { 
            // $$ = new FunctionDefinition($1, $2, nullptr, $5); 
      }
      | BType Ident LEFT_PARENTHESES FuncFParams RIGHT_PARENTHESES Block { 
            // $$ = new FunctionDefinition($1, $2, $4, $6); 
      }
      | VOID Ident LEFT_PARENTHESES RIGHT_PARENTHESES Block { 
            // $$ = new FunctionDefinition(SysType::VOID, $2, nullptr, $5); 
      }
      | VOID Ident LEFT_PARENTHESES FuncFParams RIGHT_PARENTHESES Block { 
            // $$ = new FunctionDefinition(SysType::VOID, $2, $4, $6); 
      }
      ;

FuncFParams: FuncFParam { 
            // $$ = new ArgumentList(); 
            // $$->list.emplace_back($1); 
      }
      | FuncFParams COMMA FuncFParam { 
            // $$->list.emplace_back($3); 
      }
      ;

FuncFParam: BType Ident { $$ = new Argument($1, $2); }
      | FuncFParamArray
      ;

FuncRParams: FuncRParams COMMA AddExp { $$ = $1; $$->args.push_back($3); }
           | AddExp { $$ = new FunctionCallArgList(); $$->args.push_back($1); }
           ;

FuncFParamOne: BType Ident { $$ = new Argument($1, $2); };

FuncFParamArray: FuncFParamOne LEFT_BRACKETS RIGHT_BRACKETS {
      // $$ = new Argument($1->type, *new Identifier(*(new Identifier($1->name))));
      // ((ArrayIdentifier*)&($$->name))->shape.push_back(new Number(SysType::INT,1));
      // delete $1;
      }
      | FuncFParamArray LEFT_BRACKETS Exp RIGHT_BRACKETS { 
            // $$ = $1; ((ArrayIdentifier*)&($$->name))->shape.push_back($3);; 
      }
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

Number: INTEGER { $$ = new Number(SysType::INT, $1); }
      | FLOATPOINT { $$ = new Number(SysType::FLOAT, $1); }
      ;
Ident: IDENTIFIER { $$ = new Identifier(*$1); }
      ;