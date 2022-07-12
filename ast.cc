#include "ast.h"
#include "IRBuilder.h"
// #include "syntax_analyzer.tab.h"
// Node::Node() : line_(yylloc.first_line), column_(yylloc.first_column) {}

using namespace std;

inline Type *check_sys_type(SysType type, Context &context) {
  return type == SysType::INT
             ? context.Int32Type
             : (type == SysType::FLOAT ? context.FloatType : context.VoidType);
}

void *find_symbol(Scope *scope, std::string symbol, bool is_var) {
  while (scope)
    if (is_var && scope->varDeclares_.count(symbol))
      return scope->varDeclares_[symbol];
    else if (!is_var && scope->funcDeclares_.count(symbol))
      return scope->funcDeclares_[symbol];
    else
      scope = scope->parent;
  return nullptr;
}

void Number::print() {
  string tp[3] = {"INT", "FLOAT"};
  if (static_cast<int>(type_) == 0) {
    cout << value_.i_val;
  } else if (static_cast<int>(type_) == 1) {
    cout << value_.f_val;
  }
}

void Identifier::print() {
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

void BinaryExpression::print() {
  string bop[13] = {
      "+", "-", "*", "/", "%", "<", "<=", ">", ">=", "==", "!=", "&&", "||"};
  cout << "{ ";
  lhs_->print();
  cout << " " << bop[static_cast<int>(op_)] << " ";
  rhs_->print();
  cout << "} ";
}

void LValExpression::print() { identifier_->print(); }

void UnaryExpression::print() {
  string uop[3] = {"+", "-", "!"};
  cout << uop[static_cast<int>(op_)];
  rhs_->print();
}

void ActualArgumentList::print() {
  for (auto &i : list_) {
    i->print();
  }
}

void FuncCallExpression::print() {
  cout << "<func_call>: { ";
  identifier_->print();
  if (actualArgs_ != nullptr) {
    actualArgs_->print();
  }
  cout << "}";
}

void Block::print() {
  cout << "<block>: ";
  for (auto &i : statements_) {
    if (i != nullptr)
      i->print();
  }
}

void AssignStatement::print() {
  cout << "<assign_statement>: ";
  lhs_->print();
  cout << " = ";
  rhs_->print();
}

void IfElseStatement::print() {
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

void WhileStatement::print() {
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

void BreakStatement::print() { cout << "break\n"; }

void ContinueStatement::print() { cout << "continue\n"; }

void ReturnStatement::print() {
  cout << "<return_statement>: return_val: ";
  if (value_ == nullptr) {
    cout << "nullptr";
  } else {
    value_->print();
    cout << endl;
  }
}

void EvalStatement::print() {
  cout << "<eval_statement>: ";
  value_->print();
}

void DeclareStatement::print() {
  string tp[3] = {"INT", "FLOAT", "VOID"};
  cout << "decl_type: " << tp[static_cast<int>(type_)] << endl;
  for (int i = 0; i < declares_.size(); i++) {
    cout << "    declares_[" << i << "]: ";
    declares_[i]->print();
  }
}

void VarDeclare::print() {
  cout << "<const>: " << ((isConst_ == true) ? "true" : "false") << " ";
  identifier_->print();
  cout << "<value>: ";
  if (value_ != nullptr) {
    value_->print();
  } else
    cout << "nullptr";
  cout << endl;
}

void ArrayValue::print() {
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

void ArrayDeclare::print() {
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

void FormalArgument::print() {
  string tp[3] = {"INT", "FLOAT", "VOID"};
  cout << "<type>: " << tp[static_cast<int>(type_)] << "  ";
  identifier_->print();
}

void FormalArgumentList::print() {
  for (int i = 0; i < list_.size(); i++) {
    cout << "      ";
    list_[i]->print();
    cout << endl;
  }
}

void FunctionDefinition::print() {
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

void Root::print() {
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

void Number::generate(IRBuilder *irBuilder) {
  /*switch (type_) {
  case SysType::INT:
          irBuilder->setTmpVal(ConstantInt::get(
                          Type::getInt32Type(irBuilder->getContext()),
  value_.i_val)); break; case SysType::FLOAT:
          irBuilder->setTmpVal(ConstantInt::get(
                          Type::getFloatType(irBuilder->getContext()),
  value_.f_val)); break; case SysType::VOID: break; default: break;
  }*/
}

void Root::generate(IRBuilder *irBuilder) {
  irBuilder->setScope(scope_);

  for (auto &decl : this->declareStatement_) {
    for (auto &declare_item : decl->declares_) {
      declare_item->generate(irBuilder);
    }
  }

  for (auto &funcDef : this->functionDefinitions_) {
    funcDef->generate(irBuilder);
  }
}

void VarDeclare::generate(IRBuilder *irBuilder) {
  Constant *constant = nullptr;
  if (value_ != nullptr) {
    if (value_->type_ == SysType::INT)
      constant =
          new ConstantInt(irBuilder->getModule(),
                          (irBuilder->getContext()).Int32Type, value_->value_);
    else
      constant = new ConstantFloat(irBuilder->getContext(),
                                   (irBuilder->getContext()).FloatType,
                                   value_->value_);
  }

  if (irBuilder->getScope()->parent == nullptr)
    GlobalVariable::Create(
        irBuilder->getContext(),
        type_ == SysType::INT ? (irBuilder->getContext()).Int32Type
                              : (irBuilder->getContext()).FloatType,
        identifier_->id_, isConst_, constant, irBuilder->getModule());
  else
    AllocaInst::Create(irBuilder->getContext(),
                       type_ == SysType::INT
                           ? (irBuilder->getContext()).Int32Type
                           : (irBuilder->getContext()).FloatType,
                       irBuilder->getBasicBlock(), "");
}

void ArrayDeclare::generate(IRBuilder *irBuilder) {
  Constant *constant = nullptr;
  if (value_ != nullptr) {
    if (value_->type_ == SysType::INT)
      constant =
          new ConstantInt(irBuilder->getModule(),
                          (irBuilder->getContext()).Int32Type, value_->value_);
    else
      constant = new ConstantFloat(irBuilder->getContext(),
                                   (irBuilder->getContext()).FloatType,
                                   value_->value_);
  }
}

void FunctionDefinition::generate(IRBuilder *irBuilder) {
  vector<Type *> argsType;
  for (auto arg : formalArgs_->list_)
    if ((arg->identifier_->dimension).size()) {
      size_t total_element = 1;
      if ((arg->identifier_->dimension)[0])
        for (auto &num : arg->identifier_->dimension)
          total_element *= num->value_;
      else
        total_element = -1;
      argsType.emplace_back(ArrayType::get(
          irBuilder->getContext(),
          check_sys_type(arg->type_, irBuilder->getContext()), total_element));
    } else
      argsType.emplace_back(
          check_sys_type(arg->type_, irBuilder->getContext()));

  Function::Create(
      irBuilder->getContext(),
      FunctionType::get(check_sys_type(resultType_, irBuilder->getContext()),
                        argsType),
      {}, identifier_->id_, irBuilder->getModule());
}