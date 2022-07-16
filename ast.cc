#include "ast.h"
#include "IRBuilder.h"
#include "syntax_analyzer.tab.h"
using namespace std;

Node::Node() : line_(yylloc.first_line), column_(yylloc.first_column) {}


inline Type *check_sys_type(SysType type, Context &context) {
  return type == SysType::INT
             ? context.Int32Type
             : (type == SysType::FLOAT ? context.FloatType : context.VoidType);
}

Number calc_init_val(Expression* exp, IRBuilder *irBuilder) {
	Number res{SysType::INT};
	if(dynamic_cast<Number*>(exp)) res = *dynamic_cast<Number*>(exp);
	else if(dynamic_cast<BinaryExpression*>(exp)) {
		auto bin_exp = dynamic_cast<BinaryExpression*>(exp);
		auto lhs = calc_init_val(bin_exp->lhs_, irBuilder), rhs = calc_init_val(bin_exp->rhs_, irBuilder);
		res.type_ = (lhs.type_ == SysType::FLOAT || rhs.type_ == SysType::FLOAT) ? SysType::FLOAT : SysType::INT;
		if(res.type_ == SysType::FLOAT) {
			if(lhs.type_ == SysType::INT) {
				double tmp = lhs.value_.i_val;
				lhs.value_.f_val = tmp;
			}
			if(rhs.type_ == SysType::INT) {
				double tmp = rhs.value_.i_val;
				rhs.value_.f_val = tmp;
			}
		}
		switch(bin_exp->op_) {
			case BinaryOp::ADD:
				if(res.type_ == SysType::FLOAT)
					res.value_.f_val = lhs.value_.f_val + rhs.value_.f_val;
				else
					res.value_.i_val = lhs.value_.i_val + rhs.value_.i_val; 
				break;
			case BinaryOp::SUB:
				if(res.type_ == SysType::FLOAT)
					res.value_.f_val = lhs.value_.f_val - rhs.value_.f_val;
				else
					res.value_.i_val = lhs.value_.i_val - rhs.value_.i_val; 
				break;
			case BinaryOp::MUL:
				if(res.type_ == SysType::FLOAT)
					res.value_.f_val = lhs.value_.f_val * rhs.value_.f_val;
				else
					res.value_.i_val = lhs.value_.i_val * rhs.value_.i_val; 
				break;
			case BinaryOp::DIV:
				if(res.type_ == SysType::FLOAT)
					res.value_.f_val = lhs.value_.f_val / rhs.value_.f_val;
				else
					res.value_.i_val = lhs.value_.i_val / rhs.value_.i_val; 
				break;
			case BinaryOp::MOD:
				res.value_.i_val = lhs.value_.i_val % rhs.value_.i_val;
				break;
			case BinaryOp::LT:
        if(res.type_ == SysType::FLOAT)
					res.value_.f_val = lhs.value_.f_val < rhs.value_.f_val;
				else
					res.value_.i_val = lhs.value_.i_val < rhs.value_.i_val; 
        break;
			case BinaryOp::LTE:
        if(res.type_ == SysType::FLOAT)
					res.value_.f_val = lhs.value_.f_val <= rhs.value_.f_val;
				else
					res.value_.i_val = lhs.value_.i_val <= rhs.value_.i_val; 
        break;
			case BinaryOp::GT:
        if(res.type_ == SysType::FLOAT)
					res.value_.f_val = lhs.value_.f_val > rhs.value_.f_val;
				else
					res.value_.i_val = lhs.value_.i_val > rhs.value_.i_val; 
        break;
			case BinaryOp::GTE:
        if(res.type_ == SysType::FLOAT)
					res.value_.f_val = lhs.value_.f_val >= rhs.value_.f_val;
				else
					res.value_.i_val = lhs.value_.i_val >= rhs.value_.i_val; 
        break;
			case BinaryOp::EQ:
        if(res.type_ == SysType::FLOAT)
					res.value_.f_val = lhs.value_.f_val == rhs.value_.f_val;
				else
					res.value_.i_val = lhs.value_.i_val == rhs.value_.i_val; 
        break;
			case BinaryOp::NEQ:
        if(res.type_ == SysType::FLOAT)
					res.value_.f_val = lhs.value_.f_val != rhs.value_.f_val;
				else
					res.value_.i_val = lhs.value_.i_val != rhs.value_.i_val; 
        break;
			case BinaryOp::AND:
        if(res.type_ == SysType::FLOAT)
					res.value_.i_val = lhs.value_.f_val && rhs.value_.f_val;
				else
					res.value_.i_val = lhs.value_.i_val && rhs.value_.i_val; 
        res.type_ = SysType::INT;
        break;
			case BinaryOp::OR:
        if(res.type_ == SysType::FLOAT)
					res.value_.i_val = lhs.value_.f_val || rhs.value_.f_val;
				else
					res.value_.i_val = lhs.value_.i_val || rhs.value_.i_val; 
        res.type_ = SysType::INT;
        break;
		}
	}
	else if(dynamic_cast<LValExpression*>(exp)) {
      auto lvalexp = dynamic_cast<LValExpression*>(exp);
      auto var = *irBuilder->getModule()->globalVariableList_.find(dynamic_cast<GlobalVariable*>(irBuilder->getModule()->symbolTable_[lvalexp->identifier_->id_]));
      if(dynamic_cast<ConstantArray*>(var->getInitValue())) {
        int idx = 0;
        auto arr = dynamic_cast<ConstantArray*>(var->getInitValue());
        res.type_ = dynamic_cast<ConstantZero*>(var->getInitValue())->getType()
                    == (irBuilder->getContext()).FloatType ? SysType::FLOAT : SysType::INT;
        int len = arr->dimension_.size(),
            leng = lvalexp->identifier_->dimension_.size(),
            acc = 1;
        vector<Expression*>dimension = lvalexp->identifier_->dimension_;
        //calculate the location of the multi-dimensions element
        for(int u = leng - 1;u >= 0;u--){
          idx += acc*(dynamic_cast<Number*>(dimension[u])->value_.i_val);
          acc *= arr->dimension_[u];
        }
        idx++;

        if(res.type_ == SysType::INT) res.value_.i_val = dynamic_cast<ConstantInt*>(arr->getElementValue(idx))->getValue();
        else res.value_.f_val = dynamic_cast<ConstantFloat*>(arr->getElementValue(idx))->getValue();
      }
      else if(dynamic_cast<ConstantFloat*>(var->getInitValue())){
        res.type_ = SysType::FLOAT;
        res.value_.f_val = dynamic_cast<ConstantFloat*>(var->getInitValue())->getValue();
      }
      else if(dynamic_cast<ConstantZero*>(var->getInitValue())) {
        res.type_ = dynamic_cast<ConstantZero*>(var->getInitValue())->getType()
                    == (irBuilder->getContext()).FloatType ? SysType::FLOAT : SysType::INT;
        res.value_.i_val = 0; 
      }
      else {
        res.type_ = SysType::INT;
        res.value_.i_val = dynamic_cast<ConstantInt*>(var->getInitValue())->getValue();
      }
  }
	else if(dynamic_cast<UnaryExpression*>(exp)) {
		auto unary_exp = dynamic_cast<UnaryExpression*>(exp);
		res = calc_init_val(unary_exp->rhs_, irBuilder);
		switch(unary_exp->op_){
			case UnaryOp::NEGATIVE:
        if(res.type_ == SysType::INT) res.value_.i_val = - res.value_.i_val;
        else res.value_.f_val = - res.value_.f_val;
        break;
			case UnaryOp::NOT:
        res.value_.i_val = (res.type_ == SysType::INT ? res.value_.i_val : res.value_.f_val) != 0 ? 0 : 1;
        res.type_ = SysType::INT;
      default:
        break;
		}
	}
	return res;
}

void parse_nest_array(vector<Constant *>&ans, ArrayValue *cur, bool isInt, IRBuilder *irBuilder){
  Context context = irBuilder->getContext();
  if(cur->valueList_[0]->isNumber_) {
    for(auto&val:cur->valueList_)
      if(isInt)
        ans.emplace_back(ConstantInt::get(context, 
                                          context.Int32Type, 
                                          calc_init_val(val->value_, irBuilder).value_.i_val));
      else
        ans.emplace_back(ConstantFloat::get(context,
                                            calc_init_val(val->value_, irBuilder).value_.f_val));
  }
  else 
    for(auto&arr:cur->valueList_)
      parse_nest_array(ans, arr, isInt, irBuilder);
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
  Context& context = irBuilder->getContext();

  Type *type = type_ == SysType::INT ? context.Int32Type : context.FloatType;

  Value *value = nullptr;  

  if (irBuilder->getScope()->parent == nullptr) {
    Constant *constant = nullptr;
    if (value_) {
      if (type_ == SysType::INT)
        constant = new ConstantInt(context,
                                   context.Int32Type,
                                   calc_init_val(value_, irBuilder).value_.i_val);
      else
        constant = new ConstantFloat(context,
                                     context.FloatType,
                                     calc_init_val(value_, irBuilder).value_.f_val);
    }
    value = GlobalVariable::Create(
            context,
            type,
            identifier_->id_, isConst_,
            constant == nullptr ? new ConstantZero(context,type) : constant,
            irBuilder->getModule());
  }
  else {
    value = AllocaInst::Create(context,type,
                       irBuilder->getBasicBlock(), "");
    if(value_) {
      value_->generate(irBuilder);
      StoreInst::Create(context, irBuilder->getTmpVal(), value, irBuilder->getBasicBlock());
    }
  }
  irBuilder->getScope()->DeclIR[this] = value;
}

void ArrayDeclare::generate(IRBuilder *irBuilder) {
  Context& context = irBuilder->getContext();
  Type *type = type_ == SysType::INT ? context.Int32Type
                              : context.FloatType;
  size_t total = 1;
  vector<int>dimensions{};
  int len = identifier_->dimension_.size();
  
  for(int u = 0; u < len; u++) {
    dimensions.emplace_back(calc_init_val(identifier_->dimension_[u], irBuilder).value_.i_val);
    total *= dimensions.back();
  }
  ArrayType *former, *latter;
  for(int u = len - 1; u >= 0; u--) 
    if(u == len - 1) {
      latter = ArrayType::get(context, type, dimensions[u]);
    }
    else {
      former = ArrayType::get(context, latter, dimensions[u]);
      latter = former;
    }
  ArrayType *arrType = latter;
  
  if(irBuilder->getScope()->parent == nullptr) {
    vector<Constant*>vals;
    if(value_)  //a[2][2][2]={{{1,2},{3,4}},{{5,6},{7,8}}}
      parse_nest_array(vals, value_, type_ == SysType::INT, irBuilder);
    else 
      for(int u = 0; u < total; u++) 
        vals.emplace_back(ConstantZero::get(context, type));
    GlobalVariable::Create(context, type, identifier_->id_, isConst_,
                         ConstantArray::get(context, arrType, vals, dimensions),
                         irBuilder->getModule());
  }
  else {
    AllocaInst::Create(context, arrType, irBuilder->getBasicBlock());
    
  }
}

void FunctionDefinition::generate(IRBuilder *irBuilder) {
  Context context = irBuilder->getContext();
  vector<Type *> argsType;
  string args_name[formalArgs_->list_.size()];
  int idx = 0;
  for (auto arg : formalArgs_->list_) {
    if ((arg->identifier_->dimension_).size()) {
      size_t total_element = 1;
      if ((arg->identifier_->dimension_)[0])
        for (auto &num : arg->identifier_->dimension_)
          total_element *= calc_init_val(num, irBuilder).value_.i_val;
      else
        total_element = -1;
      argsType.emplace_back(ArrayType::get(
          context,
          check_sys_type(arg->type_, context), total_element));
    } else
      argsType.emplace_back(
          check_sys_type(arg->type_, context));
    args_name[idx] = arg->identifier_->id_;
    idx++;
  } 
  irBuilder->setFunction(
      Function::Create(
      context,
      FunctionType::get(check_sys_type(returnType_, context),
                        argsType),
      args_name, identifier_->id_, irBuilder->getModule())); 
  irBuilder->setBasicBlock(
      BasicBlock::Create(
      context, 
      identifier_->id_, 
      irBuilder->getFunction())
  );
  
}