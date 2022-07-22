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
    decl->generate(irBuilder);
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
      if (!val->getType()->isPointerType()) {
        if (type_ == SysType::INT)
          constant = new ConstantInt(context,
                                    context.Int32Type,
                                    dynamic_cast<ConstantInt*>(val)->getValue());
        else
          constant = new ConstantFloat(context,
                                      context.FloatType,
                                      dynamic_cast<ConstantFloat*>(val)->getValue());
        value = constant == nullptr ? new ConstantZero(context,type) : constant;
        value = GlobalVariable::Create(
                context,
                type,
                identifier_->id_, isConst_,
                dynamic_cast<Constant*>(value),
                irBuilder->getModule());
      } else {
        value = GlobalVariable::Create(
                context,
                type,
                identifier_->id_, isConst_,
                dynamic_cast<GlobalVariable*>(val)->getInitValue(),
                irBuilder->getModule());
      }
    }
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
  Value *value;
  Context& context = irBuilder->getContext();
  Type *type = type_ == SysType::INT ? context.Int32Type
                              : context.FloatType;
  size_t total = 1;
  //nums are the suffix product of dimensions
  // e.g. a[1][2][3] => nums = {6, 6, 3};
  vector<int>dimensions{}, nums{}; 
  int len = identifier_->dimension_.size();
  for(int u = 0; u < len; u++) {
    identifier_->dimension_[u]->generate(irBuilder);
    dimensions.emplace_back(dynamic_cast<ConstantInt*>(irBuilder->getTmpVal())->getValue());
    total *= dimensions.back();
  }
  nums = dimensions;

  ArrayType *former, *latter;
  for(int u = len - 1; u >= 0; u--) 
    if(u == len - 1) {
      latter = ArrayType::get(context, type, dimensions[u]);
    }
    else {
      former = ArrayType::get(context, latter, dimensions[u]);
      latter = former;
      nums[u] *= nums[u+1];
    }
  ArrayType *arrType = latter;

  vector<Constant*>vals;
  if(value_)  
    parse_nest_array(vals, value_, 0, nums, type_ == SysType::INT, irBuilder);
  else 
    vals.resize(total, ConstantZero::get(context, type));

  if(irBuilder->getScope()->parent == nullptr) {
    value = GlobalVariable::Create(context, type, identifier_->id_, isConst_,
                                   ConstantArray::get(context, arrType, vals, dimensions),
                                   irBuilder->getModule());
  }
  else {
    BasicBlock *bb = irBuilder->getBasicBlock();
    auto arr = AllocaInst::Create(context, arrType, irBuilder->getBasicBlock());
    vector<Value*>idxList(len, ConstantInt::get(context, context.Int32Type,0));
    // TODO : call the memset function in C
    for(int u = 0; u < total; u++) {
      value = GetElementPtrInst::Create(context, arr, idxList, bb);
      StoreInst::Create(context, vals[u], value, bb);
      bool incr = true;
      // whether need to adjust the order e.g. the idxList a[1][2][3] = {3,2,1} to avoid minus operation
      for(int u = len - 1; u >= 0 && incr ; u--) {
        int curr = dynamic_cast<ConstantInt*>(idxList[u])->getValue();
        if(curr + 1 == dimensions[u]) 
          curr = 0;
        else {
          curr++;
          incr = false;
        }
        dynamic_cast<ConstantInt*>(idxList[u])->setValue(curr);
      }
    }
  }
  irBuilder->getScope()->DeclIR[this] = value;
}

void FunctionDefinition::generate(IRBuilder *irBuilder) {
  Context& context = irBuilder->getContext();
  vector<Type *> argsType;
  string args_name[formalArgs_->list_.size()];
  int idx = 0;
  for (auto arg : formalArgs_->list_) {
    if ((arg->identifier_->dimension_).empty())
        argsType.emplace_back(check_sys_type(arg->type_, context));
    else 
      argsType.emplace_back(ArrayType::get(
          context,
          check_sys_type(arg->type_, context), -1)); //-1 mean the actual dimensions is trivial to the program
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
  irBuilder->setScope(body_->scope_);
  for(int u = 0, len = formalArgs_->list_.size(); u< len; u++){
    Value *ptr;
    if(argsType[u]->isArrayType())
      ptr = AllocaInst::Create(context,
                               PointerType::get(context, static_cast<ArrayType*>(argsType[u])->getElementType()), 
                               irBuilder->getBasicBlock());
    else 
      ptr = AllocaInst::Create(context,
                               argsType[u]->isFloatType() ? context.FloatType : context.Int32Type,
                               irBuilder->getBasicBlock());
    irBuilder->getScope()->DeclIR[formalArgs_->list_[u]] = ptr;
  }
  body_->generate(irBuilder);
  irBuilder->setScope(irBuilder->getScope()->parent);
}

void BinaryExpression::generate(IRBuilder *irBuilder) {
  Context &context = irBuilder->getContext();
  Value *lhs,*rhs,*res;
  lhs_->generate(irBuilder);
  lhs = irBuilder->getTmpVal();
  if (lhs->getType()->isPointerType()) {
    lhs = dynamic_cast<GlobalVariable*>(lhs)->getInitValue();
  }
  rhs_->generate(irBuilder);
  rhs =irBuilder->getTmpVal(); 
  if (rhs->getType()->isPointerType()) {
    rhs = dynamic_cast<GlobalVariable*>(rhs)->getInitValue();
  }
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
  if (rhs->getType()->isPointerType()) {
    rhs = dynamic_cast<GlobalVariable*>(rhs)->getInitValue();
  }
  switch(op_){
			case UnaryOp::NEGATIVE:
        if(rhs->getType()->isFloatType()) {
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
        if(irBuilder->getScope()->parent) {
          auto zero = ConstantZero::get(context, context.Int1Type);
          rhs = IcmpInst::Create(context, 
                                 IcmpInst::IcmpOp::NEQ, 
                                 rhs, 
                                 zero, 
                                 irBuilder->getBasicBlock());
          res = IcmpInst::Create(context, 
                                 IcmpInst::IcmpOp::EQ, 
                                 rhs, 
                                 zero, 
                                 irBuilder->getBasicBlock());
        }
        else
          res = ConstantInt::get(context, context.Int1Type, !(dynamic_cast<ConstantInt*>(rhs)->getValue()));
        break;
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
    if(!(identifier_->dimension_.empty())){
      vector<Value *> idxList;
      for(auto&idx : identifier_->dimension_) {
        idx->generate(irBuilder);
        idxList.emplace_back(irBuilder->getTmpVal());
      }
      ptr = GetElementPtrInst::Create(context, 
                                      ptr, 
                                      idxList,
                                      irBuilder->getBasicBlock());
    }
    res = LoadInst::Create(context, 
                           ptr->getType()->getPtrElementType(), 
                           ptr, 
                           irBuilder->getBasicBlock());
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
      for(int u = leng - 1; u >= 0; u--){
        idx += acc*indice[u];
        acc *= arr->dimension_[u];
      }
      irBuilder->setTmpVal(arr->value_[idx]);
    }
  }
}

void Block::generate(IRBuilder *irBuilder) {
  irBuilder->setScope(scope_);
  // auto bb =  BasicBlock::Create(irBuilder->getContext(), "block", irBuilder->getFunction());
  // irBuilder->setBasicBlock(bb);
  for (auto& stateItem : statements_) {
    stateItem->generate(irBuilder);
  }
}

void DeclareStatement::generate(IRBuilder *irBuilder) {
  for (auto &declare_item : declares_) {
    declare_item->generate(irBuilder);
  }
}

void AssignStatement::generate(IRBuilder *irBuilder) {
  lhs_->generate(irBuilder);
  auto lval = irBuilder->getTmpVal();
  rhs_->generate(irBuilder);
  auto rval = irBuilder->getTmpVal();
  // to_do: lval and rval's type diff
  StoreInst::Create(irBuilder->getContext(), rval, lval, irBuilder->getBasicBlock());
}

void IfElseStatement::generate(IRBuilder *irBuilder) {
  Context &c = irBuilder->getContext();
  cond_->generate(irBuilder);
  auto tmpVal = irBuilder->getTmpVal();
  auto true_bb =
      BasicBlock::Create(c, "if_true_entry", irBuilder->getFunction());
  auto false_bb =
      BasicBlock::Create(c, "if_false_entry", irBuilder->getFunction());
  auto next_bb = BasicBlock::Create(c, "next_entry", irBuilder->getFunction());
  Value *condVal;
  if (tmpVal->getType()->isIntegerType()) {
    condVal = IcmpInst::Create(c, IcmpInst::IcmpOp::NEQ, tmpVal,
                               ConstantInt::get(c, Type::getInt1Type(c), 0),
                               irBuilder->getBasicBlock());
  } else {
    condVal =
        IcmpInst::Create(c, IcmpInst::IcmpOp::NEQ, tmpVal,
                         ConstantFloat::get(c, 0), irBuilder->getBasicBlock());
  }
  if (elseStmt_) {
    BranchInst::Create(c, condVal, true_bb, false_bb,
                       irBuilder->getBasicBlock());
  } else {
    BranchInst::Create(c, condVal, true_bb, next_bb,
                       irBuilder->getBasicBlock());
  }
  irBuilder->setBasicBlock(true_bb);
  thenStmt_->generate(irBuilder);
  if (!irBuilder->getBasicBlock()->hasTerminator()) {
    BranchInst::Create(c, next_bb, irBuilder->getBasicBlock());
  }
  if (elseStmt_) {
    irBuilder->setBasicBlock(false_bb);
    elseStmt_->generate(irBuilder);
    if (!irBuilder->getBasicBlock()->hasTerminator()) {
      BranchInst::Create(c, next_bb, irBuilder->getBasicBlock());
    }
  } else {
    false_bb->eraseFromParent();
  }
  irBuilder->setBasicBlock(next_bb);
}

void WhileStatement::generate(IRBuilder *irBuilder) {
  Context& c = irBuilder->getContext();
  cond_->generate(irBuilder);
  auto tmpVal = irBuilder->getTmpVal();
  auto while_bb = BasicBlock::Create(c, "while_entry", irBuilder->getFunction());
  auto next_bb = BasicBlock::Create(c, "next_entry", irBuilder->getFunction());
  Value* condVal;
  if (tmpVal->getType()->isIntegerType()) {
    condVal = IcmpInst::Create(
        c, IcmpInst::IcmpOp::NEQ, tmpVal,
        ConstantInt::get(c, Type::getInt1Type(c), 0),
        irBuilder->getBasicBlock());
  } else {
    condVal = IcmpInst::Create(c, IcmpInst::IcmpOp::NEQ, tmpVal,
                               ConstantFloat::get(c, 0),
                               irBuilder->getBasicBlock());
  }
  BranchInst::Create(c, condVal, while_bb, next_bb, irBuilder->getBasicBlock());    
  irBuilder->setBasicBlock(while_bb);
  irBuilder->setWhileBlock(while_bb);
  irBuilder->setNextBlock(next_bb);
  doStmt_->generate(irBuilder);
  if (!irBuilder->getBasicBlock()->hasTerminator()) {
    BranchInst::Create(c, condVal, while_bb, next_bb, irBuilder->getBasicBlock());    
  }
  irBuilder->setBasicBlock(next_bb);
}

void ReturnStatement::generate(IRBuilder *irBuilder) {
  Context &c = irBuilder->getContext();
  Value *retVal;
  if (value_) {
    auto ret_type = irBuilder->getFunction()->getReturnType();
    value_->generate(irBuilder);
    if (ret_type != irBuilder->getTmpVal()->getType()) {
      if (ret_type->isIntegerType()) {
        retVal =
            FpToSiInst::Create(c, Type::getInt32Type(c), irBuilder->getTmpVal(),
                               irBuilder->getBasicBlock());
      } else {
        retVal =
            SiToFpInst::Create(c, Type::getFloatType(c), irBuilder->getTmpVal(),
                               irBuilder->getBasicBlock());
      }
    }else {
      retVal = irBuilder->getTmpVal();
    }
    ReturnInst::Create(c, retVal, irBuilder->getBasicBlock());
  } else {
    ReturnInst::Create(c, irBuilder->getBasicBlock());
  }
}

void BreakStatement::generate(IRBuilder *irBuilder) {
  BranchInst::Create(irBuilder->getContext(),irBuilder->getNextBlock(),irBuilder->getBasicBlock());
}

void ContinueStatement::generate(IRBuilder *irBuilder) {
  BranchInst::Create(irBuilder->getContext(),irBuilder->getWhileBlock(),irBuilder->getBasicBlock());
}

void EvalStatement::generate(IRBuilder *irBuilder) {
  value_->generate(irBuilder);
}

void FuncCallExpression::generate(IRBuilder *irBuilder) {
  Context &context = irBuilder->getContext();
  auto func = dynamic_cast<Function*>(irBuilder->getModule()->symbolTable_[identifier_->id_]);
  auto funcType = static_cast<FunctionType*>(func->getFunctionType());
  vector<Value*>funcArgs;
  for(int u = 0, len = funcType->getArgumentsNum(); u < len; u++) {
    actualArgs_->list_[u]->generate(irBuilder);
    auto val = irBuilder->getTmpVal();
    if(dynamic_cast<ConstantInt*>(val) && funcType->getArgumentType(u) == context.FloatType)
      //SiToFpInst::Create(context, context.FloatType, val, irBuilder->getBasicBlock()); godbolt transform number without explicit instructions
      funcArgs.emplace_back(ConstantFloat::get(context, static_cast<float>(dynamic_cast<ConstantInt*>(val)->getValue())));
    else if(dynamic_cast<ConstantFloat*>(val) && funcType->getArgumentType(u) != context.FloatType) 
      funcArgs.emplace_back(ConstantInt::get(context, 
                                             funcType->getArgumentType(u),
                                             static_cast<int>(dynamic_cast<ConstantFloat*>(val)->getValue())));
    else funcArgs.emplace_back(val);
  }
  CallInst::Create(dynamic_cast<Function*>(irBuilder->getModule()->symbolTable_[identifier_->id_]),
                   funcArgs, 
                   irBuilder->getBasicBlock());
  //return value will be set by ReturnStatement::generate
} 
