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
      long long token;
      double f_val;
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
            $$->declareStatement_.emplace_back($2); 
            if($$->scope_ == nullptr) $$->scope_ = new Scope();
            for(auto&declare : $2->declares_)
                $$->scope_->varDeclares_[declare->identifier_->id_] = declare;
      }
      | CompUnit FuncDef { 
            $$ = $1; 
            $$->functionDefinitions_.emplace_back($2); 
            if($$->scope_ == nullptr) $$->scope_ = new Scope();
            $$->scope_->funcDeclares_[$2->identifier_->id_] = $2;
            $2->body_->scope_->parent = $$->scope_;
      }
      | Decl {
            root = new Root(); 
            $$ = root; 
            $$->declareStatement_.emplace_back($1);
            if($$->scope_ == nullptr) $$->scope_ = new Scope();
            for(auto&declare : $1->declares_)
                $$->scope_->varDeclares_[declare->identifier_->id_] = declare;
      }
      | FuncDef { 
            root = new Root(); 
            $$ = root; 
            $$->functionDefinitions_.emplace_back($1); 
            if($$->scope_ == nullptr) $$->scope_ = new Scope();
            $$->scope_->funcDeclares_[$1->identifier_->id_] = $1;
            $1->body_->scope_->parent = $$->scope_;
      }
      ;

Decl: ConstDecl SEMICOLON { $$ = $1;}
    | VarDecl SEMICOLON { $$ = $1; }
    ;

BType: INT { $$ = SysType::INT; }
    | FLOAT { $$ = SysType::FLOAT; }
    ;

ConstDecl: CONST BType Ident ASSIGN AddExp { 
            $$ = new DeclareStatement($2); 
            $$->declares_.emplace_back(new VarDeclare{$2, $3, $5, true}); 
      }
      | ConstDecl COMMA Ident ASSIGN AddExp { 
            $$ = $1; 
            $$->declares_.emplace_back(new VarDeclare{$1->getType(),$3, $5, true}); 
      }
      | CONST BType ArrayIdent ASSIGN ArrayVal { 
            $$ = new DeclareStatement($2); 
            $$->declares_.emplace_back(new ArrayDeclare{$2, $3, $5, true}); 
      }
      | ConstDecl COMMA ArrayIdent ASSIGN ArrayVal { 
            $$ = $1; 
            $$->declares_.emplace_back(new ArrayDeclare{$1->getType(), $3, $5, true}); 
      }
      ;

VarDecl: BType Ident { 
            $$ = new DeclareStatement($1); 
            $$->declares_.emplace_back(new VarDeclare($1, $2, nullptr, false)); 
      }
      | BType Ident ASSIGN AddExp { 
            $$ = new DeclareStatement($1); 
            $$->declares_.emplace_back(new VarDeclare($1, $2, $4, false)); 
      }
      | BType ArrayIdent { 
            $$ = new DeclareStatement($1); 
            $$->declares_.emplace_back(new ArrayDeclare($1, $2, nullptr, false)); 
      }
      | BType ArrayIdent ASSIGN ArrayVal { 
            $$ = new DeclareStatement($1); 
            $$->declares_.emplace_back(new ArrayDeclare($1, $2, $4, false)); 
      }
      | VarDecl COMMA Ident { 
            $$ = $1; 
            $$->declares_.emplace_back(new VarDeclare($1->getType(), $3, nullptr, false)); 
      }
      | VarDecl COMMA Ident ASSIGN AddExp { 
            $$ = $1; 
            $$->declares_.emplace_back(new VarDeclare($1->getType(), $3, $5, false)); 
      }
      | VarDecl COMMA ArrayIdent { 
            $$ = $1; 
            $$->declares_.emplace_back(new ArrayDeclare($1->getType(),$3, nullptr, false)); 
      }
      | VarDecl COMMA ArrayIdent ASSIGN ArrayVal { 
            $$ = $1; 
            $$->declares_.emplace_back(new ArrayDeclare($1->getType(), $3, $5, false)); 
      }
      ;

ArrayIdent: Ident LEFT_BRACKETS AddExp RIGHT_BRACKETS { $$ = $1; $$->dimension_.emplace_back($3); }
      | ArrayIdent LEFT_BRACKETS AddExp RIGHT_BRACKETS { $$ = $1; $$->dimension_.emplace_back($3); }
      ;

ArrayVal: LEFT_BRACES RIGHT_BRACES { $$ = new ArrayValue(false, nullptr); }
      | LEFT_BRACES ArrayVals RIGHT_BRACES { $$ = $2; }

ArrayVals: AddExp  { 
            $$ = new ArrayValue(false, nullptr); 
            $$->valueList_.emplace_back(new ArrayValue(true, $1)); 
      }
      | ArrayVal {
            $$ = new ArrayValue(false, nullptr);
            $$->valueList_.emplace_back($1); 
      }
      | ArrayVals COMMA AddExp {
            $$ = $1;
            $$->valueList_.emplace_back(new ArrayValue(true, $3));
      }
      | ArrayVals COMMA ArrayVal {
            $$ = $1;
            $$->valueList_.emplace_back($3);
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
            dynamic_cast<LValExpression*>($$)->identifier_->dimension_.emplace_back($3);
      }
      | ArrayItem LEFT_BRACKETS AddExp RIGHT_BRACKETS { 
            $$ = $1;
            dynamic_cast<LValExpression*>($$)->identifier_->dimension_.emplace_back($3);
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
            for(auto&arg : $4->list_) 
                $$->body_->scope_->varDeclares_[arg->identifier_->id_] = arg;
      }
      | VOID Ident LEFT_PARENTHESES RIGHT_PARENTHESES Block { 
            $$ = new FunctionDefinition(SysType::VOID, $2, nullptr, $5); 
      }
      | VOID Ident LEFT_PARENTHESES FuncFParams RIGHT_PARENTHESES Block { 
            $$ = new FunctionDefinition(SysType::VOID, $2, $4, $6); 
            for(auto&arg : $4->list_) 
                $$->body_->scope_->varDeclares_[arg->identifier_->id_] = arg;
      }
      ;

FuncFParams: FuncFParam { 
            // $$ = new std::vector<FormalArgument*>();
            // $$->emplace_back($1);
            $$ = new FormalArgumentList(); 
            $$->list_.emplace_back($1); 
      }
      | FuncFParams COMMA FuncFParam { 
            $$ = $1;
            // $$->emplace_back($3);
            $$->list_.emplace_back($3); 
      }
      ;

FuncFParam: BType Ident { $$ = new FormalArgument($1, $2); }
      | FuncFParamArray
      ;

FuncFParamArray: BType Ident LEFT_BRACKETS RIGHT_BRACKETS {
            $$ = new FormalArgument($1, $2);
            $$->identifier_->dimension_.emplace_back(nullptr);
      }
      | FuncFParamArray LEFT_BRACKETS AddExp RIGHT_BRACKETS { 
            $$ = $1;
            $$->identifier_->dimension_.emplace_back($3);
      }
      ;

FuncRParams: AddExp { $$ = new ActualArgumentList(); $$->list_.emplace_back($1); }
      | FuncRParams COMMA AddExp { $$ = $1; $$->list_.emplace_back($3); }
      ;

Block: LEFT_BRACES RIGHT_BRACES { $$ = new Block(); }
     | LEFT_BRACES BlockItems RIGHT_BRACES { 
            $$ = $2; 
            if($$->scope_ == nullptr) $$->scope_ = new Scope();
            for(auto&stmt : $2->statements_)
                if(stmt->statement_type() == StmtType::DECL)
                  for(auto&declare : stmt->declares_)
                        $$->scope_->varDeclares_[declare->identifier_->id_] = declare;
                else if(stmt->statement_type() == StmtType::Block)
                  stmt->scope_->parent = $$->scope_;
                else continue;
      }
     ;

BlockItems: BlockItem { 
            $$ = new Block(); 
            if ($1 != nullptr)
                  $$->statements_.emplace_back($1); 
      }
      | BlockItems BlockItem { 
            $$ = $1; 
            if ($1 != nullptr)
                  $$->statements_.emplace_back($2); 
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