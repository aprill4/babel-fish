#include "ast.h"
#include "IRBuilder.h"
#include <variant>
#include "syntax_analyzer.tab.h"
using namespace std;

Node::Node() : line_(yylloc.first_line), column_(yylloc.first_column) {}


inline Type *check_sys_type(SysType type, Context &context) {
  return type == SysType::INT
             ? context.Int32Type
             : (type == SysType::FLOAT ? context.FloatType : context.VoidType);
}

//return true if more than one of the operands' type is float
bool force_trans(IRBuilder *irBuilder, Value* &lhs, Value* &rhs) {
  bool is_global = irBuilder->getScope()->parent == nullptr;
  bool is_float = dynamic_cast<ConstantFloat*>(lhs) || dynamic_cast<ConstantFloat*>(rhs);
  Context &context =irBuilder->getContext();
  if(is_float) {
    if(is_global) {
      if(auto tmp = dynamic_cast<ConstantInt*>(lhs)) {
        // whether we need to delete the old constantInt
        //e.g. delete lhs;
        lhs = new ConstantFloat(context, context.FloatType, static_cast<float>(tmp->getValue()));
      } 
      if(auto tmp = dynamic_cast<ConstantInt*>(rhs)) {
        rhs = new ConstantFloat(context, context.FloatType, static_cast<float>(tmp->getValue()));
      }
    } 
    else {
      if(auto tmp = dynamic_cast<ConstantInt*>(lhs)) 
          lhs = SiToFpInst::Create(context, context.FloatType, tmp, irBuilder->getBasicBlock());
      if(auto tmp = dynamic_cast<ConstantInt*>(rhs)) 
          rhs = SiToFpInst::Create(context, context.FloatType, tmp, irBuilder->getBasicBlock());
    }
  }
  return is_float;
}

void parse_nest_array(vector<Constant *>&ans, ArrayValue *cur, int idx, vector<int>&nums, bool isInt, IRBuilder *irBuilder){
  int remain = (idx == nums.size()-1) ? 1 : nums[idx+1], 
      expect = nums[idx], 
      cnt = 0,
      original = ans.size();
  Context &context = irBuilder->getContext();

  for(auto&val : cur->valueList_) {
    if(val->isNumber_) {
      val->value_->generate(irBuilder);
      ans.emplace_back(dynamic_cast<Constant*>(irBuilder->getTmpVal()));
      if(++cnt == remain) cnt=0;
    }
    else {
      if(cnt) {
        ans.resize(ans.size() + remain - cnt, ConstantZero::get(context, isInt ? context.Int32Type : context.FloatType));
        cnt = 0;
      }
      parse_nest_array(ans, val, idx + 1, nums, isInt, irBuilder);
    }
  }

  if(ans.size()-original<expect) 
    ans.resize(expect + original, ConstantZero::get(context, isInt ? context.Int32Type : context.FloatType));
}

Value *find_symbol(Scope *scope, std::string symbol, bool is_var) {
  while (scope){
    if (is_var && scope->varDeclares_.count(symbol))
      return scope->DeclIR[scope->varDeclares_[symbol]];
    else if (!is_var && scope->funcDeclares_.count(symbol))
      return scope->funcIR[scope->funcDeclares_[symbol]];
    else
      scope = scope->parent;
  }
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
  switch (type_) {
    case SysType::INT:
          irBuilder->setTmpVal(ConstantInt::get(
                               irBuilder->getContext(),
                               Type::getInt32Type(irBuilder->getContext()),
                               value_.i_val));
        break; 
    case SysType::FLOAT:
          irBuilder->setTmpVal(ConstantFloat::get(
                               irBuilder->getContext(),
                               value_.f_val)); 
          break;
    default: break;
  }
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
      value_->generate(irBuilder);
      auto val = irBuilder->getTmpVal();
      if (type_ == SysType::INT)
        constant = new ConstantInt(context,
                                   context.Int32Type,
                                   dynamic_cast<ConstantInt*>(val)->getValue());
      else
        constant = new ConstantFloat(context,
                                     context.FloatType,
                                     dynamic_cast<ConstantFloat*>(val)->getValue());
    }
    value = constant == nullptr ? new ConstantZero(context,type) : constant;
    GlobalVariable::Create(
            context,
            type,
            identifier_->id_, isConst_,
            dynamic_cast<Constant*>(value),
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
    identifier_->dimension_[u]->generate(irBuilder);
    dimensions.emplace_back(dynamic_cast<ConstantInt*>(irBuilder->getTmpVal()));
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
    if(value_)  //a[2][2][3]={{{1,2},{}},{{5,6}},}
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
          ;//total_element *= calc_init_val(num, irBuilder).value_.i_val;
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

void BinaryExpression::generate(IRBuilder *irBuilder) {
  Context &context = irBuilder->getContext();
  Value *lhs,*rhs,*res;
  lhs_->generate(irBuilder);
  lhs = irBuilder->getTmpVal(); 
  rhs_->generate(irBuilder);
  rhs =irBuilder->getTmpVal(); 
  bool is_float = force_trans(irBuilder, lhs, rhs);
  
  switch(op_) {
			case BinaryOp::ADD:
				if(is_float) {
          if(irBuilder->getScope()->parent) 
            res = BinaryInst::CreateFadd(context, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantFloat::get(context, 
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() + dynamic_cast<ConstantFloat*>(rhs)->getValue());
        }
				else {
          if(irBuilder->getScope()->parent) 
            res = BinaryInst::CreateAdd(context, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int32Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() + dynamic_cast<ConstantInt*>(rhs)->getValue());
        }
				break;
			case BinaryOp::SUB:
				if(is_float) {
          if(irBuilder->getScope()->parent) 
            res = BinaryInst::CreateFsub(context, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantFloat::get(context, 
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() - dynamic_cast<ConstantFloat*>(rhs)->getValue());
        }
				else {
          if(irBuilder->getScope()->parent) 
            res = BinaryInst::CreateSub(context, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int32Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() - dynamic_cast<ConstantInt*>(rhs)->getValue());
        }
				break;
			case BinaryOp::MUL:
				if(is_float) {
          if(irBuilder->getScope()->parent) 
            res = BinaryInst::CreateFmul(context, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantFloat::get(context, 
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() * dynamic_cast<ConstantFloat*>(rhs)->getValue());
        }
				else {
          if(irBuilder->getScope()->parent) 
            res = BinaryInst::CreateMul(context, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int32Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() * dynamic_cast<ConstantInt*>(rhs)->getValue());
        }
				break;
			case BinaryOp::DIV:
				if(is_float) {
          if(irBuilder->getScope()->parent) 
            res = BinaryInst::CreateFdiv(context, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantFloat::get(context, 
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() / dynamic_cast<ConstantFloat*>(rhs)->getValue());
        }
				else {
          if(irBuilder->getScope()->parent) 
            res = BinaryInst::CreateSdiv(context, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int32Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() / dynamic_cast<ConstantInt*>(rhs)->getValue());
        }
				break;
			case BinaryOp::MOD:
         if(irBuilder->getScope()->parent) 
            res = BinaryInst::CreateMod(context, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int32Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() % dynamic_cast<ConstantInt*>(rhs)->getValue());
				break;
			case BinaryOp::LT:
        if(is_float) {
          if(irBuilder->getScope()->parent) 
            res = FcmpInst::Create(context, FcmpInst::FcmpOp::LT, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() < dynamic_cast<ConstantFloat*>(rhs)->getValue());
        }
				else {
          if(irBuilder->getScope()->parent) 
            res = IcmpInst::Create(context, IcmpInst::IcmpOp::LT, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() < dynamic_cast<ConstantInt*>(rhs)->getValue());
        }
        break;
			case BinaryOp::LTE:
        if(is_float) {
          if(irBuilder->getScope()->parent) 
            res = FcmpInst::Create(context, FcmpInst::FcmpOp::LTE, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() <= dynamic_cast<ConstantFloat*>(rhs)->getValue());
        }
				else {
          if(irBuilder->getScope()->parent) 
            res = IcmpInst::Create(context, IcmpInst::IcmpOp::LTE, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() <= dynamic_cast<ConstantInt*>(rhs)->getValue());
        }
        break;
			case BinaryOp::GT:
        if(is_float) {
          if(irBuilder->getScope()->parent) 
            res = FcmpInst::Create(context, FcmpInst::FcmpOp::GT, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() > dynamic_cast<ConstantFloat*>(rhs)->getValue());
        }
				else {
          if(irBuilder->getScope()->parent) 
            res = IcmpInst::Create(context, IcmpInst::IcmpOp::GT, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() > dynamic_cast<ConstantInt*>(rhs)->getValue());
        } 
        break;
			case BinaryOp::GTE:
        if(is_float) {
          if(irBuilder->getScope()->parent) 
            res = FcmpInst::Create(context, FcmpInst::FcmpOp::GTE, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() >= dynamic_cast<ConstantFloat*>(rhs)->getValue());
        }
				else {
          if(irBuilder->getScope()->parent) 
            res = IcmpInst::Create(context, IcmpInst::IcmpOp::GTE, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() >= dynamic_cast<ConstantInt*>(rhs)->getValue());
        } 
        break;
			case BinaryOp::EQ:
        if(is_float) {
          if(irBuilder->getScope()->parent) 
            res = FcmpInst::Create(context, FcmpInst::FcmpOp::EQ, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() == dynamic_cast<ConstantFloat*>(rhs)->getValue());
        }
				else {
          if(irBuilder->getScope()->parent) 
            res = IcmpInst::Create(context, IcmpInst::IcmpOp::EQ, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() == dynamic_cast<ConstantInt*>(rhs)->getValue());
        } 
        break;
			case BinaryOp::NEQ:
        if(is_float) {
          if(irBuilder->getScope()->parent) 
            res = FcmpInst::Create(context, FcmpInst::FcmpOp::NEQ, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() != dynamic_cast<ConstantFloat*>(rhs)->getValue());
        }
				else {
          if(irBuilder->getScope()->parent) 
            res = IcmpInst::Create(context, IcmpInst::IcmpOp::NEQ, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() != dynamic_cast<ConstantInt*>(rhs)->getValue());
        } 
        break;
			case BinaryOp::AND:
        if(irBuilder->getScope()->parent) 
            res = BinaryInst::CreateAnd(context, lhs, rhs, irBuilder->getBasicBlock());
        else 
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() && dynamic_cast<ConstantInt*>(rhs)->getValue());
        break;
			case BinaryOp::OR:
        if(irBuilder->getScope()->parent) 
            res = BinaryInst::CreateOr(context, lhs, rhs, irBuilder->getBasicBlock());
        else 
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() || dynamic_cast<ConstantInt*>(rhs)->getValue());
        break;
      default: break;
		}

    irBuilder->setTmpVal(res);
}

void UnaryExpression::generate(IRBuilder *irBuilder) {
  Context &context = irBuilder->getContext();
  rhs_->generate(irBuilder);
  Value *rhs = irBuilder->getTmpVal(), *res;

  switch(op_){
			case UnaryOp::NEGATIVE:
        if(dynamic_cast<ConstantFloat*>(rhs)) {
          if(irBuilder->getScope()->parent) 
            res = BinaryInst::CreateFsub(context, ConstantFloat::get(context, 0), rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantFloat::get(context, -dynamic_cast<ConstantFloat*>(rhs)->getValue());
        }
				else {
          if(irBuilder->getScope()->parent) 
            res = BinaryInst::CreateSub(context, ConstantInt::get(context, context.Int32Type, 0), rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int32Type, -dynamic_cast<ConstantInt*>(rhs)->getValue());
        }
        break;
			case UnaryOp::NOT:
        res = ConstantInt::get(context, context.Int1Type, !(dynamic_cast<ConstantInt*>(rhs)->getValue()));
      default:
        break;
	}
  
  irBuilder->setTmpVal(res);
}

void LValExpression::generate(IRBuilder *irBuilder) {
  Context &context = irBuilder->getContext();
  Scope *scope = irBuilder->getScope();

  if(irBuilder->getScope()->parent) {
    Value *ptr = find_symbol(scope, identifier_->id_, true), *res;
    if(identifier_->dimension_.empty()){
      auto res = LoadInst::Create(context, 
                                  ptr->getType(), 
                                  ptr, 
                                  irBuilder->getBasicBlock());
    }
    else {
      vector<Value *> idxList;
      for(auto&idx : identifier_->dimension_) {
        idx->generate(irBuilder);
        idxList.emplace_back(irBuilder->getTmpVal());
      }
       res = GetElementPtrInst::Create(context, 
                                       ptr, 
                                       idxList,
                                       irBuilder->getBasicBlock());
    }
    irBuilder->setTmpVal(res);
  }
  else {
    if(identifier_->dimension_.empty()) {
      auto target = scope->DeclIR[scope->varDeclares_[identifier_->id_]];
      irBuilder->setTmpVal(target);
    }
    else {
      auto arr = dynamic_cast<ConstantArray*>(scope->DeclIR[scope->varDeclares_[identifier_->id_]]);
      vector<int>indice;
      for(auto&idx : identifier_->dimension_) {
        idx->generate(irBuilder);
        indice.emplace_back(dynamic_cast<ConstantInt*>(irBuilder->getTmpVal())->getValue());
      }
      int len = arr->dimension_.size(),
            leng = indice.size(),
            acc = 1, idx = 0; 
      //calculate the location of the multi-dimensions element
      for(int u = leng - 1;u >= 0;u--){
        idx += acc*indice[u];
        acc *= arr->dimension_[u];
      }
      irBuilder->setTmpVal(arr->value_[idx]);
    }
  }
}

void AssignStatement::generate(IRBuilder *irBuilder) {
  auto scope = irBuilder->getScope();
  auto irVal = find_symbol(scope, static_cast<LValExpression*>(lhs_)->identifier_->id_ , true);
  rhs_->generate(irBuilder);
  StoreInst::Create(irBuilder->getContext(), irBuilder->getTmpVal(), irVal, irBuilder->getBasicBlock());
}

void IfElseStatement::generate(IRBuilder *irBuilder) {
  auto scope = irBuilder->getScope();
  if (elseStmt_) {
    
  } else {
    auto cond_bb = BasicBlock::Create(irBuilder->getContext(), "if_cond_entry", irBuilder->getFunction());
    auto then_bb = BasicBlock::Create(irBuilder->getContext(), "if_then_entry", irBuilder->getFunction());
    // BranchInst::Create()
  }
}

void ReturnStatement::generate(IRBuilder *irBuilder) {
  auto scope = irBuilder->getScope();
  if (value_) {
    value_->generate(irBuilder);
    ReturnInst::Create(irBuilder->getContext(), irBuilder->getTmpVal(), irBuilder->getBasicBlock());
  }else {
    ReturnInst::Create(irBuilder->getContext(), irBuilder->getBasicBlock());
  }
}

void EvalStatement::generate(IRBuilder *irBuilder) {
  value_->generate(irBuilder);
}

void FuncCallExpression::generate(IRBuilder *irBuilder) {
  auto func = dynamic_cast<Function*>(irBuilder->getModule()->symbolTable_[identifier_->id_]);
  func->getFunctionType();
} 
