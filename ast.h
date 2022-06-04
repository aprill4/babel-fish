#pragma once
#include <iostream>
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
  virtual void print(){};
};

class Expression : public Node {
public:
};

class Statement : public Node {
public:
};

class Number : public Expression {
public:
  Number(SysType type) : type(type) {}
  Number(SysType type, int i_val) : Number(type) { value.i_val = i_val; }
  Number(SysType type, float f_val) : Number(type) { value.f_val = f_val; }

public:
  SysType type;
  union {
    int i_val;
    float f_val;
  } value;
};

class Identifier : public Node {
public:
  Identifier(const std::string &id) : id(id) {}
  void print() {
    using namespace std;
    cout << "<id>: " << id;
    cout << "  <dimension>: ";
    if (dimension.empty()) {
      cout << "not_array";
    } else {
      for (auto &i : dimension) {
        if (i == nullptr)
          cout << "[]";
        else
          cout << "[" << dynamic_cast<Number *>(i)->value.i_val << "]";
      }
    }
  }

public:
  std::string id;
  std::vector<Expression *> dimension;
};

class BinaryExpression : public Expression {
public:
  BinaryExpression(Expression *left_expr, BinaryOp op, Expression *right_expr)
      : left_expr(left_expr), op(op), right_expr(right_expr) {}

public:
  Expression *left_expr;
  BinaryOp op;
  Expression *right_expr;
};

class LValExpression : public Expression {
public:
  LValExpression(Identifier *identifier) : identifier(identifier) {}

public:
  Identifier *identifier;
  std::vector<Expression *> dimension;
};

class UnaryExpression : public Expression {
public:
  UnaryExpression(UnaryOp op, Expression *rhs) : op(op), rexpr(rhs) {}

public:
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
  void print() {
    using namespace std;
    cout << "assign\n";
  }

public:
  Expression *lhs;
  Expression *rhs;
};

class IfElseStatement : public Statement {
public:
  IfElseStatement(Expression *cond, Statement *thenstmt, Statement *elsestmt)
      : cond(cond), thenstmt(thenstmt), elsestmt(elsestmt) {}
  void print() {
    using namespace std;
    cout << "ifelse\n";
  }

public:
  Expression *cond;
  Statement *thenstmt;
  Statement *elsestmt;
};

class WhileStatement : public Statement {
public:
  WhileStatement(Expression *cond, Statement *dostmt)
      : cond(cond), dostmt(dostmt) {}
  void print() {
    using namespace std;
    cout << "while\n";
  }

public:
  Expression *cond;
  Statement *dostmt;
};

class VoidStatement : public Statement {
public:
  void print() {
    using namespace std;
    cout << "void\n";
  }
};

class BreakStatement : public Statement {
public:
  void print() {
    using namespace std;
    cout << "break\n";
  }
};

class ContinueStatement : public Statement {
public:
  void print() {
    using namespace std;
    cout << "continue\n";
  }
};

class ReturnStatement : public Statement {
public:
  ReturnStatement(Expression *value = NULL) : value(value) {}
  void print() {
    using namespace std;
    cout << "return\n";
  }

public:
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
  void print() {
    using namespace std;
    string tp[3] = {"INT", "FLOAT", "VOID"};
    cout << "decl_type: " << tp[static_cast<int>(type)] << endl;
    for (int i = 0; i < defs.size(); i++) {
      cout << "    defs[" << i << "]: ";
      defs[i]->print();
    }
  }
};

class VarDeclare : public Declare {
public:
  VarDeclare(Identifier *identifier, Expression *value, bool is_const)
      : identifier(identifier), value(value), is_const(is_const) {}
  void print() {
    using namespace std;
    cout << "<const>: " << ((is_const == true) ? "true" : "false");
    cout << "  <id>: " << identifier->id;
    cout << "  <init_val>: " << dynamic_cast<Number *>(value)->value.i_val
         << endl;
  }

public:
  Identifier *identifier;
  Expression *value;
  bool is_const;
};

class ArrayDeclareInitValue : public Expression {
public:
  ArrayDeclareInitValue(bool is_number, Expression *value)
      : is_number(is_number), value(value) {}
  void print() {
    using namespace std;
    if (is_number == true) {
      cout << dynamic_cast<Number *>(value)->value.i_val;
    } else {
      for (int i = 0; i < value_list.size(); i++) {
        if (value_list[i]->is_number) {
          value_list[i]->print();
        } else {
          cout << "{";
          value_list[i]->print();
          cout << "}";
        }
        if (i < value_list.size() - 1)
          cout << ", ";
      }
    }
  }

public:
  bool is_number;
  Expression *value;
  std::vector<ArrayDeclareInitValue *> value_list;
};

class ArrayDeclare : public Declare {
public:
  ArrayDeclare(Identifier *identifier, ArrayDeclareInitValue *value,
               bool is_const)
      : identifier(identifier), value(value), is_const(is_const) {}
  void print() {
    using namespace std;
    cout << "<const>: " << ((is_const == true) ? "true" : "false") << "  ";
    identifier->print();
    cout << "  <init_val>: {";
    value->print();
    cout << "}";
  }

public:
  Identifier *identifier;
  ArrayDeclareInitValue *value;
  bool is_const;
};

class Argument : public Expression {
public:
  Argument(SysType type, Identifier *identifier)
      : type(type), identifier(identifier) {}
  void print() {
    using namespace std;
    string tp[3] = {"INT", "FLOAT", "VOID"};
    cout << "<type>: " << tp[static_cast<int>(type)] << "  ";
    identifier->print();
  }

public:
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
  void print() {
    using namespace std;
    string tp[3] = {"INT", "FLOAT", "VOID"};
    cout << "return_type: " << tp[static_cast<int>(return_type)];
    cout << "  id: " << identifier->id << endl;
    if (args == nullptr)
      cout << "    args: nullptr" << endl;
    else {
      cout << "    args: " << endl;
      for (int i = 0; i < args->list.size(); i++) {
        cout << "      ";
        args->list[i]->print();
        cout << endl;
      }
    }
    cout << "    statements: ";
    if (body->statements.empty()) {
      cout << "nullptr\n";
    } else {
      for (auto &i : body->statements) {
        i->print();
      }
    }
  }

public:
  SysType return_type;
  Identifier *identifier;
  ArgumentList *args;
  Block *body;
};

class Root : public Node {
public:
  std::vector<DeclareStatement *> decls;
  std::vector<FunctionDefinition *> func_defs;
  void print() {
    using namespace std;
    cout << "[root]:\n";
    cout << "  decls: " << decls.size() << endl;
    cout << "  func_defs: " << func_defs.size() << endl;
    cout << "[decls]: " << endl;
    for (int i = 0; i < decls.size(); i++) {
      cout << "  decl[" << i << "]: ";
      decls[i]->print();
      cout << endl;
    }
    cout << "[func_defs]: " << endl;
    for (int i = 0; i < func_defs.size(); i++) {
      cout << "  func_defs[" << i << "]: ";
      func_defs[i]->print();
    }
  }
};