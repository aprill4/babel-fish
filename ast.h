#pragma once
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

class Node {
public:
  Node();
  ~Node(){};
  virtual void print(){};

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
  Number(SysType type, long long i_val) : Number(type) { value_.i_val = i_val; }
  Number(SysType type, double f_val) : Number(type) { value_.f_val = f_val; }
  void print() {
    using namespace std;
    string tp[3] = {"INT", "FLOAT"};
    if (static_cast<int>(type_) == 0) {
      cout << value_.i_val;
    } else if (static_cast<int>(type_) == 1) {
      cout << value_.f_val;
    }
  }

public:
  SysType type_;
  union {
    long long i_val;
    double f_val;
  } value_;
};

class Identifier : public Node {
public:
  Identifier(const std::string *id) : id_(*id) {}
  void print() {
    using namespace std;
    cout << "<id>: " << id_;
    cout << " <dimension>: ";
    if (dimension_.empty()) {
      cout << "not_array";
    } else {
      for (auto &i : dimension_) {
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
  std::string id_;
  std::vector<Expression *> dimension_;
};

class BinaryExpression : public Expression {
public:
  BinaryExpression(Expression *lhs, BinaryOp op, Expression *rhs)
      : lhs_(lhs), op_(op), rhs_(rhs) {}
  void print() {
    using namespace std;
    string bop[13] = {
        "+", "-", "*", "/", "%", "<", "<=", ">", ">=", "==", "!=", "&&", "||"};
    cout << "{ ";
    lhs_->print();
    cout << " " << bop[static_cast<int>(op_)] << " ";
    rhs_->print();
    cout << "} ";
  }

public:
  Expression *lhs_;
  BinaryOp op_;
  Expression *rhs_;
};

class LValExpression : public Expression {
public:
  LValExpression(Identifier *identifier) : identifier_(identifier) {}
  void print() {
    using namespace std;
    identifier_->print();
  }

public:
  Identifier *identifier_;
};

class UnaryExpression : public Expression {
public:
  UnaryExpression(UnaryOp op, Expression *rhs) : op_(op), rhs_(rhs) {}
  void print() {
    using namespace std;
    string uop[3] = {"+", "-", "!"};
    cout << uop[static_cast<int>(op_)];
    rhs_->print();
  }

public:
  UnaryOp op_;
  Expression *rhs_;
};

class ActualArgumentList : public Node {
public:
  void print() {
    using namespace std;
    for (auto &i : list_) {
      i->print();
    }
  }

public:
  std::vector<Expression *> list_;
};

class FuncCallExpression : public Expression {
public:
  FuncCallExpression(Identifier *identifier, ActualArgumentList *actualArgs)
      : identifier_(identifier), actualArgs_(actualArgs) {}
  void print() {
    using namespace std;
    cout << "<func_call>: { ";
    identifier_->print();
    if (actualArgs_ != nullptr) {
      actualArgs_->print();
    }
    cout << "}";
  }

public:
  Identifier *identifier_;
  ActualArgumentList *actualArgs_;
};

class Statement : public Node {
public:
  virtual StmtType statement_type() {
    return StmtType::OTHER;
  }
};

class Block : public Statement {
public:
  void print() {
    using namespace std;
    cout << "<block>: ";
    for (auto &i : statements_) {
      if (i != nullptr)
        i->print();
    }
  }
  StmtType statement_type() {
    return StmtType::BLOCK;
  }

public:
  Scope *scope_;
  std::vector<Statement *> statements_;
};

class AssignStatement : public Statement {
public:
  AssignStatement(Expression *lhs, Expression *rhs) : lhs_(lhs), rhs_(rhs) {}
  void print() {
    using namespace std;
    cout << "<assign_statement>: ";
    lhs_->print();
    cout << " = ";
    rhs_->print();
  }

public:
  Expression *lhs_;
  Expression *rhs_;
};

class IfElseStatement : public Statement {
public:
  IfElseStatement(Expression *cond, Statement *thenStmt, Statement *elseStmt)
      : cond_(cond), thenStmt_(thenStmt), elseStmt_(elseStmt) {}
  void print() {
    using namespace std;
    cout << "<ifelse_statement>: ";
    cout << "{<cond>: ";
    if (cond_ != nullptr)
      cond_->print();
    cout << "} ";
    cout << "{<then>: ";
    if (thenStmt_ != nullptr)
      thenStmt_->print();
    cout << "} ";
    cout << "{<else>: ";
    if (elseStmt_ != nullptr)
      elseStmt_->print();
    cout << "} ";
  }

public:
  Expression *cond_;
  Statement *thenStmt_;
  Statement *elseStmt_;
};

class WhileStatement : public Statement {
public:
  WhileStatement(Expression *cond, Statement *doStmt)
      : cond_(cond), doStmt_(doStmt) {}
  void print() {
    using namespace std;
    cout << "<while_statement>: ";
    cout << "{<cond>: ";
    if (cond_ != nullptr)
      cond_->print();
    cout << "} ";
    cout << "{<do>: ";
    if (doStmt_ != nullptr)
      doStmt_->print();
    cout << "} ";
  }

public:
  Expression *cond_;
  Statement *doStmt_;
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
  ReturnStatement(Expression *value = nullptr) : value_(value) {}
  void print() {
    using namespace std;
    cout << "<return_statement>: return_val: ";
    if (value_ == nullptr) {
      cout << "nullptr";
    } else {
      value_->print();
      cout << endl;
    }
  }

public:
  Expression *value_;
};

class EvalStatement : public Statement {
public:
  EvalStatement(Expression *value) : value_(value) {}
  void print() {
    using namespace std;
    cout << "<eval_statement>: ";
    value_->print();
  }

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
  void print() {
    using namespace std;
    string tp[3] = {"INT", "FLOAT", "VOID"};
    cout << "decl_type: " << tp[static_cast<int>(type_)] << endl;
    for (int i = 0; i < declares_.size(); i++) {
      cout << "    declares_[" << i << "]: ";
      declares_[i]->print();
    }
  }
  SysType getType() { return type_; }
  virtual StmtType statement_type() {
    return StmtType::DECL;
  }

public:
  SysType type_;
  std::vector<Declare *> declares_;
};

class VarDeclare : public Declare {
public:
  VarDeclare(SysType type, Identifier *identifier, Expression *value,
             bool is_const)
      : Declare(type, identifier, is_const), value_(value) {}
  void print() {
    using namespace std;
    cout << "<const>: " << ((isConst_ == true) ? "true" : "false") << " ";
    identifier_->print();
    cout << "<value>: ";
    if (value_ != nullptr) {
      value_->print();
    } else
      cout << "nullptr";
    cout << endl;
  }

public:
  Expression *value_;
};

class ArrayValue : public Expression {
public:
  ArrayValue(bool is_number, Expression *value)
      : isNumber_(is_number), value_(value) {}
  void print() {
    using namespace std;
    if (isNumber_ == true) {
      value_->print();
    } else {
      for (int i = 0; i < valueList_.size(); i++) {
        if (valueList_[i]->isNumber_) {
          valueList_[i]->print();
        } else {
          cout << "{";
          valueList_[i]->print();
          cout << "}";
        }
        if (i < valueList_.size() - 1)
          cout << ", ";
      }
    }
  }

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
  void print() {
    using namespace std;
    cout << "<const>: " << ((isConst_ == true) ? "true" : "false") << " ";
    identifier_->print();
    cout << "<init_val>: ";
    if (value_ != nullptr) {
      cout << "{";
      value_->print();
      cout << "}";
    } else
      cout << "nullptr";
  }

public:
  ArrayValue *value_;
};

class FormalArgument : public Declare {
public:
  FormalArgument(SysType type, Identifier *identifier)
      : Declare(type, identifier, false) {}
  void print() {
    using namespace std;
    string tp[3] = {"INT", "FLOAT", "VOID"};
    cout << "<type>: " << tp[static_cast<int>(type_)] << "  ";
    identifier_->print();
  }
};

class FormalArgumentList : public Node {
public:
  FormalArgumentList() = default;
  void print() {
    using namespace std;
    for (int i = 0; i < list_.size(); i++) {
      cout << "      ";
      list_[i]->print();
      cout << endl;
    }
  }

public:
  std::vector<FormalArgument *> list_;
};

class FunctionDefinition : public Node {
public:
  FunctionDefinition(SysType returnType, Identifier *identifier,
                     FormalArgumentList *formalArgs, Block *body)
      : returnType_(returnType), identifier_(identifier),
        formalArgs_(formalArgs), body_(body) {}
  void print() {
    using namespace std;
    string tp[3] = {"INT", "FLOAT", "VOID"};
    cout << "return_type: " << tp[static_cast<int>(returnType_)];
    cout << "  id: " << identifier_->id_ << endl;
    if (formalArgs_ == nullptr)
      cout << "    args: nullptr" << endl;
    else {
      cout << "    args: " << endl;
      formalArgs_->print();
    }
    cout << "    statements: ";
    if (body_->statements_.empty()) {
      cout << "nullptr\n";
    } else {
      cout << endl;
      // body->print();
      for (auto &i : body_->statements_) {
        cout << "      ";
        if (i != nullptr)
          i->print();
        cout << endl;
      }
    }
  }

public:
  SysType returnType_;
  Identifier *identifier_;
  FormalArgumentList *formalArgs_;
  Block *body_;
};

class Scope {
public:
  Scope() { parent = nullptr; }

public:
  Scope *parent;
  std::map<std::string, Declare *> varDeclares_;
  std::map<std::string, FunctionDefinition *> funcDeclares_;
};

class Root : public Node {
public:
  Root() = default;
  void print() {
    using namespace std;
    cout << "[root]:\n";
    cout << "  declareStatement_: " << declareStatement_.size() << endl;
    cout << "  functionDefinition_: " << functionDefinitions_.size() << endl;
    cout << "[declareStatement_]: " << endl;
    for (int i = 0; i < declareStatement_.size(); i++) {
      cout << "  decl[" << i << "]: ";
      declareStatement_[i]->print();
      cout << endl;
    }
    cout << "[functionDefinition_]: " << endl;
    for (int i = 0; i < functionDefinitions_.size(); i++) {
      cout << "  functionDefinition_[" << i << "]: ";
      functionDefinitions_[i]->print();
    }
  }

public:
  std::vector<DeclareStatement *> declareStatement_;
  std::vector<FunctionDefinition *> functionDefinitions_;
  Scope *scope_;
};

void *find_symbol(Scope *scope, std::string symbol, bool is_var);