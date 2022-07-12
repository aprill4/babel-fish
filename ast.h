#pragma once
#include "IR/include/Value.h"
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
enum class SysType { INT, FLOAT, VOID };

enum class BinaryOp {
  ADD,
  SUB,
  MUL,
  DIV,
  MOD,
  LT,
  LTE,
  GT,
  GTE,
  EQ,
  NEQ,
  AND,
  OR
};

enum class UnaryOp { POSITIVE, NEGATIVE, NOT };

enum class StmtType { BLOCK, DECL, OTHER };

class IRBuilder;

class Node {
public:
  Node();
  ~Node(){};
  virtual void print(){};
  virtual void generate(IRBuilder *irBuilder){};

public:
  int line_, column_;
};

class Scope;

class Expression : public Node {
public:
};

class Number : public Expression {
public:
  Number(SysType type) : type_(type) {}
  Number(SysType type, std::int32_t i_val) : Number(type) {
    value_.i_val = i_val;
  }
  Number(SysType type, float f_val) : Number(type) { value_.f_val = f_val; }
  void print() override;
  void generate(IRBuilder *irBuilder) override;

public:
  SysType type_;
  union {
    std::int32_t i_val;
    float f_val;
  } value_;
};

class Identifier : public Node {
public:
  Identifier(const std::string *id) : id_(*id) {}
  void print();

public:
  std::string id_;
  std::vector<Expression *> dimension_;
};

class BinaryExpression : public Expression {
public:
  BinaryExpression(Expression *lhs, BinaryOp op, Expression *rhs)
      : lhs_(lhs), op_(op), rhs_(rhs) {}
  void print();
  void generate(IRBuilder *irBuilder) override;

public:
  Expression *lhs_;
  BinaryOp op_;
  Expression *rhs_;
};

class LValExpression : public Expression {
public:
  LValExpression(Identifier *identifier) : identifier_(identifier) {}
  void print();

public:
  Identifier *identifier_;
};

class UnaryExpression : public Expression {
public:
  UnaryExpression(UnaryOp op, Expression *rhs) : op_(op), rhs_(rhs) {}
  void print();

public:
  UnaryOp op_;
  Expression *rhs_;
};

class ActualArgumentList : public Node {
public:
  void print();

public:
  std::vector<Expression *> list_;
};

class FuncCallExpression : public Expression {
public:
  FuncCallExpression(Identifier *identifier, ActualArgumentList *actualArgs)
      : identifier_(identifier), actualArgs_(actualArgs) {}
  void print();
  void generate(IRBuilder *irBuilder) override;

public:
  Identifier *identifier_;
  ActualArgumentList *actualArgs_;
};

class Statement : public Node {
public:
  virtual StmtType statement_type() { return StmtType::OTHER; }
};

class Block : public Statement {
public:
  void print();
  StmtType statement_type() { return StmtType::BLOCK; }

public:
  Scope *scope_;
  std::vector<Statement *> statements_;
};

class AssignStatement : public Statement {
public:
  AssignStatement(Expression *lhs, Expression *rhs) : lhs_(lhs), rhs_(rhs) {}
  void print();
  void generate(IRBuilder *irBuilder) override;

public:
  Expression *lhs_;
  Expression *rhs_;
};

class IfElseStatement : public Statement {
public:
  IfElseStatement(Expression *cond, Statement *thenStmt, Statement *elseStmt)
      : cond_(cond), thenStmt_(thenStmt), elseStmt_(elseStmt) {}
  void print();
  void generate(IRBuilder *irBuilder) override;

public:
  Expression *cond_;
  Statement *thenStmt_;
  Statement *elseStmt_;
};

class WhileStatement : public Statement {
public:
  WhileStatement(Expression *cond, Statement *doStmt)
      : cond_(cond), doStmt_(doStmt) {}
  void print();
  void generate(IRBuilder *irBuilder) override;

public:
  Expression *cond_;
  Statement *doStmt_;
};

class BreakStatement : public Statement {
public:
  void print();
  void generate(IRBuilder *irBuilder) override;
};

class ContinueStatement : public Statement {
public:
  void print();
};

class ReturnStatement : public Statement {
public:
  ReturnStatement(Expression *value = nullptr) : value_(value) {}
  void print();
  void generate(IRBuilder *irBuilder) override;

public:
  Expression *value_;
};

class EvalStatement : public Statement {
public:
  EvalStatement(Expression *value) : value_(value) {}
  void print();

public:
  Expression *value_;
};

class Declare : public Node {
public:
  Declare(SysType type, Identifier *identifier, bool isConst)
      : type_(type), identifier_(identifier), isConst_(isConst) {}

public:
  SysType type_;
  Identifier *identifier_;
  bool isConst_;
};

class DeclareStatement : public Statement {
public:
  DeclareStatement(SysType type) : type_(type) {}
  SysType getType() { return type_; }
  virtual StmtType statement_type() { return StmtType::DECL; }
  void print();

public:
  SysType type_;
  std::vector<Declare *> declares_;
};

class VarDeclare : public Declare {
public:
  VarDeclare(SysType type, Identifier *identifier, Expression *value,
             bool is_const)
      : Declare(type, identifier, is_const), value_(value) {}
  void print();
  void generate(IRBuilder *irBuilder) override;

public:
  Expression *value_;
};

class ArrayValue : public Expression {
public:
  ArrayValue(bool is_number, Expression *value)
      : isNumber_(is_number), value_(value) {}
  void print();

public:
  bool isNumber_;
  Expression *value_;
  std::vector<ArrayValue *> valueList_;
};

class ArrayDeclare : public Declare {
public:
  ArrayDeclare(SysType type, Identifier *identifier, ArrayValue *value,
               bool is_const)
      : Declare(type, identifier, is_const), value_(value) {}
  void print();
  void generate(IRBuilder *irBuilder) override;

public:
  ArrayValue *value_;
};

class FormalArgument : public Declare {
public:
  FormalArgument(SysType type, Identifier *identifier)
      : Declare(type, identifier, false) {}
  void print();
};

class FormalArgumentList : public Node {
public:
  FormalArgumentList() = default;
  void print();
  void generate(IRBuilder *irBuilder) override;

public:
  std::vector<FormalArgument *> list_;
};

class FunctionDefinition : public Node {
public:
  FunctionDefinition(SysType returnType, Identifier *identifier,
                     FormalArgumentList *formalArgs, Block *body)
      : returnType_(returnType), identifier_(identifier),
        formalArgs_(formalArgs), body_(body) {}
  void print();
  void generate(IRBuilder *irBuilder) override;

public:
  SysType returnType_;
  Identifier *identifier_;
  FormalArgumentList *formalArgs_;
  Block *body_;
};

class Scope {
public:
  Scope() { parent = nullptr; }
  void print();

public:
  Scope *parent;
  std::map<std::string, Declare *> varDeclares_;
  std::map<Declare *, Value *> DeclIR;
  std::map<std::string, FunctionDefinition *> funcDeclares_;
  std::map<FunctionDefinition *, Value *> funcIR;
};

class Root : public Node {
public:
  Root() = default;
  void print() override;
  void generate(IRBuilder *irBuilder) override;

public:
  std::vector<DeclareStatement *> declareStatement_;
  std::vector<FunctionDefinition *> functionDefinitions_;
  Scope *scope_;
};

void *find_symbol(Scope *scope, std::string symbol, bool is_var);