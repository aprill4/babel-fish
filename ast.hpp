#pragma once
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

class Context;

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

class ASTNode;

ASTNode *current();

class ASTNode {
public:
  int line, column;
  ASTNode();
  virtual ~ASTNode();

protected:
};

class ASTExpression : public ASTNode {
public:
protected:
};

class ASTStatement : public ASTExpression {
protected:
};

class Identifier : public ASTNode {
public:
  Identifier(const std::string &id) : id(id) {}
  std::string id;
  std::vector<ASTExpression *> dimension;
};

class ASTNumber : public ASTExpression {
public:
  SysType type;
  union {
    int i_val;
    float f_val;
  } value;
  ASTNumber(SysType type) : type(type) {}
  ASTNumber(SysType type, int i_val) : ASTNumber(type) { value.i_val = i_val; }
  ASTNumber(SysType type, float f_val) : ASTNumber(type) {
    value.f_val = f_val;
  }
};

class ASTCondExpression : public ASTExpression {
public:
  ASTCondExpression(ASTExpression *value);
  ASTExpression *value;
};

class ASTBinaryExpression : public ASTExpression {
public:
  ASTBinaryExpression(ASTExpression *lhs, BinaryOp op, ASTExpression *rhs)
      : lexpr(lhs), rexpr(rhs), op(op) {}
  BinaryOp op;
  ASTExpression *lexpr;
  ASTExpression *rexpr;
};

class ASTUnaryExpression : public ASTExpression {
public:
  ASTUnaryExpression(UnaryOp op, ASTExpression *rhs) : op(op), rexpr(rhs) {}
  UnaryOp op;
  ASTExpression *rexpr;
};

class CommaExpression : public ASTExpression {
public:
  CommaExpression() = default;
  std::vector<ASTExpression *> values;
};

class FunctionCallArgList : public ASTExpression {
public:
  std::vector<ASTExpression *> args;
};

class FunctionCall : public ASTExpression {
public:
  Identifier &name;
  FunctionCallArgList &args;
  FunctionCall(Identifier &name, FunctionCallArgList &args);

protected:
};

class Block : public ASTStatement {
public:
  std::vector<ASTStatement *> statements;

protected:
};

class AssignStatement : public ASTStatement {
public:
  Identifier &lhs;
  ASTExpression &rhs;
  AssignStatement(Identifier &lhs, ASTExpression &rhs);

protected:
};

class AfterInc : public ASTStatement {
public:
  int op;
  Identifier &lhs;
  AfterInc(Identifier &lhs, int op);

protected:
};

class IfElseStatement : public ASTStatement {
public:
  ASTCondExpression &cond;
  ASTStatement &thenstmt;
  ASTStatement &elsestmt;
  IfElseStatement(ASTCondExpression &cond, ASTStatement &thenstmt,
                  ASTStatement &elsestmt);
};

class WhileStatement : public ASTStatement {
public:
  ASTCondExpression &cond;
  ASTStatement &dostmt;
  WhileStatement(ASTCondExpression &cond, ASTStatement &dostmt);
};

class BreakStatement : public ASTStatement {};

class ContinueStatement : public ASTStatement {};

class ReturnStatement : public ASTStatement {
public:
  ASTExpression *value;
  ReturnStatement(ASTExpression *value = NULL);
};

class EvalStatement : public ASTStatement {
public:
  ASTExpression &value;
  EvalStatement(ASTExpression &value);
};

class VoidStatement : public ASTStatement {};

class ASTDeclare : public ASTNode {};

class ASTDeclareStatement : public ASTStatement {
public:
  ASTDeclareStatement(SysType type) : type(type) {}
  SysType type;
  std::vector<ASTDeclare *> defs;
};

class VarDeclare : public ASTDeclare {
public:
  VarDeclare(Identifier *identifier, ASTExpression *value, bool is_const)
      : identifier(identifier), value(value), is_const(is_const) {}
  Identifier *identifier;
  ASTExpression *value;
  bool is_const;
};

class ArrayDeclareInitValue : public ASTExpression {
public:
  ArrayDeclareInitValue(bool is_number, ASTExpression *value);
  bool is_number;
  ASTExpression *value;
  std::vector<ArrayDeclareInitValue *> value_list;
};

class ArrayIdentifier : public Identifier {
public:
  ArrayIdentifier(Identifier &name) : Identifier(name), name(name) {}
  Identifier &name;
  std::vector<ASTExpression *> shape;
};

class ArrayDeclare : public ASTDeclare {
public:
  ArrayDeclare(Identifier *identifier, ArrayDeclareInitValue *value,
               bool is_const)
      : identifier(identifier), value(value), is_const(is_const) {}
  Identifier *identifier;
  ArrayDeclareInitValue *value;
  bool is_const;
};

class Argument : public ASTExpression {
public:
  Argument(SysType type, std::string id) : type(type), id(id) {}
  SysType type;
  std::string id;
};

class ArgumentList : public ASTExpression {
public:
  std::vector<Argument *> list;
};

class FunctionDefinition : public ASTNode {
public:
  FunctionDefinition(SysType return_type, std::string id, ArgumentList *args,
                     Block *body)
      : return_type(return_type), id(id), args(args), body(body) {}
  SysType return_type;
  std::string id;
  ArgumentList *args;
  Block *body;
};

class ASTRoot : public ASTNode {
public:
  std::vector<ASTDeclareStatement *> decls;
  std::vector<FunctionDefinition *> func_defs;
};