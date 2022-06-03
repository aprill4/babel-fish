#pragma once
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

class Node {
public:
  int line, column;
  Node();
  virtual ~Node(){};

protected:
};

class Expression : public Node {
public:
protected:
};

class Statement : public Node {
protected:
};

class Identifier : public Node {
public:
  Identifier(const std::string &id) : id(id) {}
  std::string id;
  std::vector<Expression *> dimension;
};

class Number : public Expression {
public:
  SysType type;
  union {
    int i_val;
    float f_val;
  } value;
  Number(SysType type) : type(type) {}
  Number(SysType type, int i_val) : Number(type) { value.i_val = i_val; }
  Number(SysType type, float f_val) : Number(type) { value.f_val = f_val; }
};

class BinaryExpression : public Expression {
public:
  BinaryExpression(Expression *lhs, BinaryOp op, Expression *rhs)
      : lexpr(lhs), rexpr(rhs), op(op) {}
  BinaryOp op;
  Expression *lexpr;
  Expression *rexpr;
};

class LValExpression : public Expression {
public:
  LValExpression(Identifier *identifier) : identifier(identifier) {}
  Identifier *identifier;
  std::vector<Expression *> dimension;
};

class UnaryExpression : public Expression {
public:
  UnaryExpression(UnaryOp op, Expression *rhs) : op(op), rexpr(rhs) {}
  UnaryOp op;
  Expression *rexpr;
};

class FunctionCallArgList : public Expression {
public:
  std::vector<Expression *> args;
};

class FunctionCall : public Expression {
public:
  FunctionCall(Identifier *name, FunctionCallArgList *args)
      : name(name), args(args) {}
  Identifier *name;
  FunctionCallArgList *args;

protected:
};

class Block : public Statement {
public:
  std::vector<Statement *> statements;

protected:
};

class AssignStatement : public Statement {
public:
  AssignStatement(Expression *lhs, Expression *rhs) : lhs(lhs), rhs(rhs) {}
  Expression *lhs;
  Expression *rhs;

protected:
};

class IfElseStatement : public Statement {
public:
  IfElseStatement(Expression *cond, Statement *thenstmt, Statement *elsestmt)
      : cond(cond), thenstmt(thenstmt), elsestmt(elsestmt) {}
  Expression *cond;
  Statement *thenstmt;
  Statement *elsestmt;
};

class WhileStatement : public Statement {
public:
  WhileStatement(Expression *cond, Statement *dostmt)
      : cond(cond), dostmt(dostmt) {}
  Expression *cond;
  Statement *dostmt;
};

class VoidStatement : public Statement {};

class BreakStatement : public Statement {};

class ContinueStatement : public Statement {};

class ReturnStatement : public Statement {
public:
  ReturnStatement(Expression *value = NULL) : value(value) {}
  Expression *value;
};

class EvalStatement : public Statement {
public:
  EvalStatement(Expression *value) : value(value) {}
  Expression *value;
};

class Declare : public Node {};

class DeclareStatement : public Statement {
public:
  DeclareStatement(SysType type) : type(type) {}
  SysType type;
  std::vector<Declare *> defs;
};

class VarDeclare : public Declare {
public:
  VarDeclare(Identifier *identifier, Expression *value, bool is_const)
      : identifier(identifier), value(value), is_const(is_const) {}
  Identifier *identifier;
  Expression *value;
  bool is_const;
};

class ArrayDeclareInitValue : public Expression {
public:
  ArrayDeclareInitValue(bool is_number, Expression *value)
      : is_number(is_number), value(value) {}
  bool is_number;
  Expression *value;
  std::vector<ArrayDeclareInitValue *> value_list;
};

class ArrayDeclare : public Declare {
public:
  ArrayDeclare(Identifier *identifier, ArrayDeclareInitValue *value,
               bool is_const)
      : identifier(identifier), value(value), is_const(is_const) {}
  Identifier *identifier;
  ArrayDeclareInitValue *value;
  bool is_const;
};

class Argument : public Expression {
public:
  Argument(SysType type, Identifier *identifier)
      : type(type), identifier(identifier) {}
  SysType type;
  Identifier *identifier;
};

class ArgumentList : public Expression {
public:
  std::vector<Argument *> list;
};

class FunctionDefinition : public Node {
public:
  FunctionDefinition(SysType return_type, Identifier *identifier,
                     ArgumentList *args, Block *body)
      : return_type(return_type), identifier(identifier), args(args),
        body(body) {}
  SysType return_type;
  Identifier *identifier;
  ArgumentList *args;
  Block *body;
};

class Root : public Node {
public:
  std::vector<DeclareStatement *> decls;
  std::vector<FunctionDefinition *> func_defs;
};