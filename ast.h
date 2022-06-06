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
  Node();
  virtual ~Node(){};
  virtual void print(){};

public:
  int line, column;
};

class Expression : public Node {
public:
};

class Number : public Expression {
public:
  Number(SysType type) : type(type) {}
  Number(SysType type, int i_val) : Number(type) { value.i_val = i_val; }
  Number(SysType type, float f_val) : Number(type) { value.f_val = f_val; }
  void print() {
    using namespace std;
    string tp[3] = {"INT", "FLOAT"};
    if (static_cast<int>(type) == 0) {
      cout << value.i_val;
    } else if (static_cast<int>(type) == 1) {
      cout << value.f_val;
    }
  }

public:
  SysType type;
  union {
    int i_val;
    float f_val;
  } value;
};

class Identifier : public Node {
public:
  Identifier(const std::string *id) : id(*id) {}
  void print() {
    using namespace std;
    cout << "<id>: " << id;
    cout << " <dimension>: ";
    if (dimension.empty()) {
      cout << "not_array";
    } else {
      for (auto &i : dimension) {
        if (i == nullptr)
          cout << "[]";
        else {
          cout << "[";
          i->print();
          cout << "]";
        }
      }
    }
    cout << " ";
  }

public:
  std::string id;
  std::vector<Expression *> dimension;
};

class BinaryExpression : public Expression {
public:
  BinaryExpression(Expression *left_expr, BinaryOp op, Expression *right_expr)
      : left_expr(left_expr), op(op), right_expr(right_expr) {}
  void print() {
    using namespace std;
    string bop[13] = {
        "+", "-", "*", "/", "%", "<", "<=", ">", ">=", "==", "!=", "&&", "||"};
    cout << "{ ";
    left_expr->print();
    cout << " " << bop[static_cast<int>(op)] << " ";
    right_expr->print();
    cout << "} ";
  }

public:
  Expression *left_expr;
  BinaryOp op;
  Expression *right_expr;
};

class LValExpression : public Expression {
public:
  LValExpression(Identifier *identifier) : identifier(identifier) {}
  void print() {
    using namespace std;
    identifier->print();
  }

public:
  Identifier *identifier;
};

class UnaryExpression : public Expression {
public:
  UnaryExpression(UnaryOp op, Expression *right_expr)
      : op(op), right_expr(right_expr) {}
  void print() {
    using namespace std;
    string uop[3] = {"+", "-", "!"};
    cout << uop[static_cast<int>(op)];
    right_expr->print();
  }

public:
  UnaryOp op;
  Expression *right_expr;
};

class FuncCallArgumentList : public Expression {
public:
  void print() {
    using namespace std;
    for (auto &i : list) {
      i->print();
    }
  }

public:
  std::vector<Expression *> list;
};

class FuncCallExpression : public Expression {
public:
  FuncCallExpression(Identifier *identifier, FuncCallArgumentList *args)
      : identifier(identifier), args(args) {}
  void print() {
    using namespace std;
    cout << "<func_call>: { ";
    identifier->print();
    if (args != nullptr) {
      args->print();
    }
    cout << "}";
  }

public:
  Identifier *identifier;
  FuncCallArgumentList *args;
};

class Statement : public Node {
public:
};

class Block : public Statement {
public:
  void print() {
    using namespace std;
    cout << "<block>: ";
    for (auto &i : statements) {
      if (i != nullptr)
        i->print();
    }
  }

public:
  std::vector<Statement *> statements;
};

class AssignStatement : public Statement {
public:
  AssignStatement(Expression *left_expr, Expression *right_expr)
      : left_expr(left_expr), right_expr(right_expr) {}
  void print() {
    using namespace std;
    cout << "<assign_statement>: ";
    left_expr->print();
    cout << " = ";
    right_expr->print();
  }

public:
  Expression *left_expr;
  Expression *right_expr;
};

class IfElseStatement : public Statement {
public:
  IfElseStatement(Expression *cond, Statement *then_stmt, Statement *else_stmt)
      : cond(cond), then_stmt(then_stmt), else_stmt(else_stmt) {}
  void print() {
    using namespace std;
    cout << "<ifelse_statement>: ";
    cout << "{<cond>: ";
    if (cond != nullptr)
      cond->print();
    cout << "} ";
    cout << "{<then>: ";
    if (then_stmt != nullptr)
      then_stmt->print();
    cout << "} ";
    cout << "{<else>: ";
    if (else_stmt != nullptr)
      else_stmt->print();
    cout << "} ";
  }

public:
  Expression *cond;
  Statement *then_stmt;
  Statement *else_stmt;
};

class WhileStatement : public Statement {
public:
  WhileStatement(Expression *cond, Statement *do_stmt)
      : cond(cond), do_stmt(do_stmt) {}
  void print() {
    using namespace std;
    cout << "<while_statement>: ";
    cout << "{<cond>: ";
    if (cond != nullptr)
      cond->print();
    cout << "} ";
    cout << "{<do>: ";
    if (do_stmt != nullptr)
      do_stmt->print();
    cout << "} ";
  }

public:
  Expression *cond;
  Statement *do_stmt;
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
  ReturnStatement(Expression *value = nullptr) : value(value) {}
  void print() {
    using namespace std;
    cout << "<return_statement>: return_val: ";
    if (value == nullptr) {
      cout << "nullptr";
    } else {
      value->print();
      cout << endl;
    }
  }

public:
  Expression *value;
};

class EvalStatement : public Statement {
public:
  EvalStatement(Expression *value) : value(value) {}
  void print() {
    using namespace std;
    cout << "<eval_statement>: ";
    value->print();
  }

public:
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
    cout << "<const>: " << ((is_const == true) ? "true" : "false") << " ";
    identifier->print();
    cout << "<value>: ";
    if (value != nullptr) {
      value->print();
    } else
      cout << "nullptr";
    cout << endl;
  }

public:
  Identifier *identifier;
  Expression *value;
  bool is_const;
};

class ArrayValue : public Expression {
public:
  ArrayValue(bool is_number, Expression *value)
      : is_number(is_number), value(value) {}
  void print() {
    using namespace std;
    if (is_number == true) {
      value->print();
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
  std::vector<ArrayValue *> value_list;
};

class ArrayDeclare : public Declare {
public:
  ArrayDeclare(Identifier *identifier, ArrayValue *value,
               bool is_const)
      : identifier(identifier), value(value), is_const(is_const) {}
  void print() {
    using namespace std;
    cout << "<const>: " << ((is_const == true) ? "true" : "false") << " ";
    identifier->print();
    cout << "<init_val>: ";
    if (value != nullptr) {
      cout << "{";
      value->print();
      cout << "}";
    } else
      cout << "nullptr";
  }

public:
  Identifier *identifier;
  ArrayValue *value;
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
  ArgumentList() = default;
  void print() {
    using namespace std;
    for (int i = 0; i < list.size(); i++) {
      cout << "      ";
      list[i]->print();
      cout << endl;
    }
  }

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
      args->print();
    }
    cout << "    statements: ";
    if (body->statements.empty()) {
      cout << "nullptr\n";
    } else {
      cout << endl;
      // body->print();
      for (auto &i : body->statements) {
        cout << "      ";
        if (i != nullptr)
          i->print();
        cout << endl;
      }
    }
  }

public:
  SysType return_type;
  Identifier *identifier;
  ArgumentList *args;
  Block *body;
};

class Scope {
public:
  Scope() = default;

public:
  std::vector<DeclareStatement *> var_declares;
};

class Root : public Node {
public:
  Root() = default;
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

public:
  std::vector<DeclareStatement *> decls;
  std::vector<FunctionDefinition *> func_defs;
  Scope *scope;
};