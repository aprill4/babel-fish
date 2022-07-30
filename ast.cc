#include "ast.h"
#include "Exception.h"
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

void parse_nest_array(vector<Value *>&ans, ArrayValue *cur, int idx, vector<int>&nums, bool isInt, IRBuilder *irBuilder){
  Context &context = irBuilder->getContext();
  int remain = (idx == nums.size() - 1) ? 1 : nums[idx+1], 
      expect = nums[idx], 
      cnt = 0,
      original = ans.size();

  for(auto&val : cur->valueList_) {
    if (val->isNumber_) {
      val->value_->generate(irBuilder);
      if (isInt && irBuilder->getTmpVal()->getType()->isFloatType()) {
        throw Exception("array type is int, element isn't float");
      }
      ans.emplace_back(irBuilder->getTmpVal());
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
    if (is_var && scope->DeclIR.count(symbol))
      return scope->DeclIR[symbol];
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
  cout << "{ ";
  cout << uop[static_cast<int>(op_)];
  rhs_->print();
  cout << "} ";
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

void addLibFn(IRBuilder *irBuilder, string name,Scope* scope_,Type * returnType,std::vector<Type *>argsType){
  Context& c = irBuilder->getContext();

  auto funty = FunctionType::get(returnType,argsType);
  string parms[1] = {"i"};
  auto fl = new FormalArgumentList();
  string *s = new string("i");
  auto id = new Identifier(s);
  fl->list_.emplace_back(new FormalArgument(SysType::INT,id));
  string *s2 = new string(name);
  auto id2 = new Identifier(s);
  FunctionDefinition* fde = new FunctionDefinition(SysType::VOID,id2,fl, nullptr);
  auto x =   Function::Create(c, funty, parms, name, irBuilder->getModule(), true);
  scope_->funcIR[fde] = x;
  BasicBlock* bb = BasicBlock::Create(c, name, x);
  if (returnType->isVoidType()) {
    ReturnInst::Create(c,bb);  
  }else{
    ReturnInst::Create(c,ConstantInt::get(c, returnType, 0),bb);  
  }
}

void Root::generate(IRBuilder *irBuilder) {
  Context&c = irBuilder->getContext();
  irBuilder->setScope(scope_);
  addLibFn(irBuilder, "putint" , scope_, Type::getVoidType(c),{Type::getInt32Type(c)});
  addLibFn(irBuilder, "putch" , scope_, Type::getVoidType(c),{Type::getInt32Type(c)});
  // addLibFn(irBuilder, "putarray" , scope_, Type::getVoidType(c),{Type::getInt32Type(c),Type::getArrayType(c,Type::getInt32Type(c),1)});
  addLibFn(irBuilder, "getint" , scope_, Type::getInt32Type(c),{});
  addLibFn(irBuilder, "getch" , scope_, Type::getInt32Type(c),{});
  // addLibFn(irBuilder, "getarray" , scope_, Type::getArrayType(c,Type::getInt32Type(c),1),{});
  for (auto &decl : this->declareStatement_) {
    decl->generate(irBuilder);
  }

  for (auto &funcDef : this->functionDefinitions_) {
    funcDef->generate(irBuilder);
  }
}

void VarDeclare::generate(IRBuilder *irBuilder) {
  Context& context = irBuilder->getContext();
  Type *type = (type_ == SysType::INT) ? context.Int32Type : context.FloatType;
  Value *value = nullptr;  
  if (irBuilder->getScope()->inGlobal()) {
    Constant *constant = nullptr;
    if (value_) {
      value_->generate(irBuilder);
      auto val = irBuilder->getTmpVal();
      if (dynamic_cast<GlobalVariable*>(val)) {
        val = dynamic_cast<GlobalVariable*>(val)->getInitValue();
      }
      auto init_val = val->getType()->isIntegerType()
                          ? dynamic_cast<ConstantInt *>(val)->getValue()
                          : dynamic_cast<ConstantFloat *>(val)->getValue();
      if (type_ == SysType::INT) {
        constant = new ConstantInt(context, context.Int32Type, init_val);
      } else {
        constant = new ConstantFloat(context, context.FloatType, init_val);
      }
      value = GlobalVariable::Create(
              context,
              type,
              identifier_->id_, isConst_,
              constant,
              irBuilder->getModule());
    } else {
      value = GlobalVariable::Create(
              context,
              type,
              identifier_->id_, isConst_,
              new ConstantZero(context, type),
              irBuilder->getModule());    
    }
  } else {
    if (isConst_) {
      value = AllocaInst::Create(context, type, irBuilder->getBasicBlock());
      if (value_) {
        value_->generate(irBuilder);
        auto val = irBuilder->getTmpVal(); 
        cout << val->print() << endl;
        StoreInst::Create(context, val, value, irBuilder->getBasicBlock());
        if (val->getType()->isPointerType()) {
          throw Exception("var init_val isn't const");
        }
        auto init_val = val->getType()->isIntegerType() ? dynamic_cast<ConstantInt*>(val)->getValue() : 
                dynamic_cast<ConstantFloat*>(val)->getValue();
        if (val->getType()->isIntegerType()) {
          value = ConstantInt::get(context, type, init_val);
        } else if (val->getType()->isFloatType()) {
          value = ConstantFloat::get(context, init_val);
        }
      } else {
        value = ConstantZero::get(context, type); 
      }
    } else {
      value = AllocaInst::Create(context, type, irBuilder->getBasicBlock());
      if(value_) {
        value_->generate(irBuilder);
        auto init_val = irBuilder->getTmpVal();
        if (init_val->getType()->isPointerType()) {
          init_val = LoadInst::Create(context, init_val, irBuilder->getBasicBlock());
        }
        if (init_val->getType() != type) {
          if (type->isIntegerType()) {
            init_val = FpToSiInst::Create(context, context.Int32Type, init_val, irBuilder->getBasicBlock());
          } else {
            init_val = SiToFpInst::Create(context, context.FloatType, init_val, irBuilder->getBasicBlock());
          }
        }
        StoreInst::Create(context, init_val, value, irBuilder->getBasicBlock());
      } else {
        StoreInst::Create(context, ConstantZero::get(context, type), value, irBuilder->getBasicBlock());        
      }
    }
  }
  irBuilder->getScope()->DeclIR[identifier_->id_] = value;
}

void ArrayDeclare::generate(IRBuilder *irBuilder) {
  Value *value;
  Context& context = irBuilder->getContext();
  Type *type = type_ == SysType::INT ? context.Int32Type
                              : context.FloatType;
  size_t total = 1;
  //nums are the suffix product of dimensions
  // e.g. a[1][2][3] => nums = {6, 6, 3};
  vector<int> dimensions{}, nums{}; 
  int len = identifier_->dimension_.size();
  for(int u = 0; u < len; u++) {
    identifier_->dimension_[u]->generate(irBuilder);
    auto tmp = irBuilder->getTmpVal();
    if (dynamic_cast<GlobalVariable*>(tmp)) {
      if (!dynamic_cast<GlobalVariable*>(tmp)->isConst()) {
        throw Exception("array dimension is not const");    
      }
      tmp = dynamic_cast<GlobalVariable*>(tmp)->getInitValue();
    } else if (!dynamic_cast<ConstantInt*>(tmp)) {
        throw Exception("array dimension is not const");    
    }
    dimensions.emplace_back(dynamic_cast<ConstantInt*>(tmp)->getValue());
    total *= dimensions.back();
  }
  nums = dimensions;

  ArrayType *former, *latter;
  for(int u = len - 1; u >= 0; u--) {
    if(u == len - 1) {
      latter = ArrayType::get(context, type, dimensions[u]);
    }
    else {
      former = ArrayType::get(context, latter, dimensions[u]);
      latter = former;
      nums[u] *= nums[u+1];
    }
  }
  ArrayType *arrType = latter;
  vector<Value*> vals;
  if(value_)  
    parse_nest_array(vals, value_, 0, nums, type_ == SysType::INT, irBuilder);
  else 
    vals.resize(total, ConstantZero::get(context, type));

  if(irBuilder->getScope()->inGlobal()) {
    value = GlobalVariable::Create(context, arrType, identifier_->id_, isConst_,
                                   ConstantArray::get(context, arrType, vals, dimensions),
                                   irBuilder->getModule());
  }
  else {
    if (isConst_) {
      AllocaInst::Create(context, arrType, irBuilder->getBasicBlock());
      value = ConstantArray::get(context, arrType, vals, dimensions);
    } else {      
      BasicBlock *bb = irBuilder->getBasicBlock();
      value = AllocaInst::Create(context, arrType, irBuilder->getBasicBlock());
      vector<Value*> idxList;
      for (int i = 0; i < len; i++) {
        idxList.emplace_back(ConstantInt::get(context, context.Int32Type,0));
      }
      // TODO : call the memset function in C
      Value* tmp;
      for(int u = 0; u < total; u++) {
        idxList.insert(idxList.begin(), ConstantInt::get(context, context.Int32Type, 0));
        tmp = GetElementPtrInst::Create(context, value, idxList, bb);
        idxList.erase(idxList.begin());
        auto temp_val = vals[u];
        if (temp_val->getType()->isPointerType()) {
          temp_val = LoadInst::Create(context, temp_val, bb);
        }
        if (temp_val->getType() != type) {
          if (type->isIntegerType()) {
            temp_val = FpToSiInst::Create(context, context.Int32Type, temp_val, irBuilder->getBasicBlock());
          } else {
            temp_val = SiToFpInst::Create(context, context.FloatType, temp_val, irBuilder->getBasicBlock());
          }
        }
        StoreInst::Create(context, temp_val, tmp, bb);
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
  }
  irBuilder->getScope()->DeclIR[identifier_->id_] = value;
}

void FunctionDefinition::generate(IRBuilder *irBuilder) {
  Context& context = irBuilder->getContext();
  vector<Type *> argsType;
  string args_name[formalArgs_->list_.size()];
  int idx = 0;
  for (auto arg : formalArgs_->list_) {
    if ((arg->identifier_->dimension_).empty()) {
        argsType.emplace_back(check_sys_type(arg->type_, context));
    } else {
      vector<int> dimension;
      for (auto i : arg->identifier_->dimension_) {
        if (i) {
          i->generate(irBuilder);
          dimension.emplace_back(
              dynamic_cast<ConstantInt *>(irBuilder->getTmpVal())->getValue());
        }
      }
      if (dimension.size() != 0) {
        argsType.emplace_back(PointerType::get(context,
            ArrayType::get(context, check_sys_type(arg->type_, context),
                           dimension)));
      } else {
        argsType.emplace_back(PointerType::get(context, check_sys_type(arg->type_, context)));
      }
    }
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
    if (argsType[u]->isArrayType()) {
      ptr = AllocaInst::Create(context, static_cast<ArrayType*>(argsType[u]), 
                               irBuilder->getBasicBlock());
      StoreInst::Create(context, irBuilder->getFunction()->getArgument(u), ptr, irBuilder->getBasicBlock());
    } else if (argsType[u]->isPointerType()){
      ptr = AllocaInst::Create(context, static_cast<PointerType*>(argsType[u]), 
                               irBuilder->getBasicBlock());
      StoreInst::Create(context, irBuilder->getFunction()->getArgument(u), ptr, irBuilder->getBasicBlock());
    } else {
      ptr = AllocaInst::Create(context,
                               argsType[u]->isFloatType() ? context.FloatType : context.Int32Type,
                               irBuilder->getBasicBlock());
      StoreInst::Create(context, irBuilder->getFunction()->getArgument(u), ptr, irBuilder->getBasicBlock());
    } 
    irBuilder->getScope()->DeclIR[args_name[u]] = ptr;
  }
  body_->generate(irBuilder);
  if (!irBuilder->getBasicBlock()->hasTerminator()) {
    if (returnType_ == SysType::VOID) {  
      ReturnInst::Create(context,irBuilder->getBasicBlock());
    } else {
      ReturnInst::Create(context, ConstantZero::get(context, check_sys_type(returnType_, context)), irBuilder->getBasicBlock());
    }
  }
  irBuilder->setScope(irBuilder->getScope()->parent);
}

void BinaryExpression::generate(IRBuilder *irBuilder) {
  Context &context = irBuilder->getContext();
  Value *lhs = nullptr, *rhs = nullptr, *res = nullptr;
  bool is_float = false;
  if (op_ != BinaryOp::OR && op_ != BinaryOp::AND) {
    lhs_->generate(irBuilder);
    lhs = irBuilder->getTmpVal();
    if (lhs->getType()->isPointerType()) {
      if (dynamic_cast<GlobalVariable*>(lhs) && dynamic_cast<GlobalVariable*>(lhs)->isConst()) {
        lhs = dynamic_cast<GlobalVariable*>(lhs)->getInitValue();
      } else if (irBuilder->getScope()->inGlobal()) {
        lhs = dynamic_cast<GlobalVariable*>(lhs)->getInitValue();
      } else {
        lhs = LoadInst::Create(context, lhs, irBuilder->getBasicBlock());
      }
    }
    rhs_->generate(irBuilder);
    rhs =irBuilder->getTmpVal(); 
    if (rhs->getType()->isPointerType()) {
      if (dynamic_cast<GlobalVariable*>(rhs) && dynamic_cast<GlobalVariable*>(rhs)->isConst() ) {
        rhs = dynamic_cast<GlobalVariable*>(rhs)->getInitValue();
      } else if (irBuilder->getScope()->inGlobal()) {
        rhs = dynamic_cast<GlobalVariable*>(rhs)->getInitValue();
      } else {
        rhs = LoadInst::Create(context, rhs->getType()->getPtrElementType(), rhs, irBuilder->getBasicBlock());
      }
    }
    is_float = force_trans(irBuilder, lhs, rhs);
  }
  // cout << lhs->print() << endl;
  // cout << rhs->print() << endl;
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
          if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(rhs)) {
            res = ConstantInt::get(context, context.Int32Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() + dynamic_cast<ConstantInt*>(rhs)->getValue());
          }
          else if(!irBuilder->getScope()->inGlobal()) 
            res = BinaryInst::CreateAdd(context, lhs, rhs, irBuilder->getBasicBlock());
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
          if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(rhs)) {
            res = ConstantInt::get(context, context.Int32Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() - dynamic_cast<ConstantInt*>(rhs)->getValue());
          }
          else if(irBuilder->getScope()->parent) 
            res = BinaryInst::CreateSub(context, lhs, rhs, irBuilder->getBasicBlock());
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
          if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(rhs)) {
            res = ConstantInt::get(context, context.Int32Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() * dynamic_cast<ConstantInt*>(rhs)->getValue());
          }
          else if(irBuilder->getScope()->parent) 
            res = BinaryInst::CreateMul(context, lhs, rhs, irBuilder->getBasicBlock());
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
          if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(rhs)) {
            res = ConstantInt::get(context, context.Int32Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() / dynamic_cast<ConstantInt*>(rhs)->getValue());
          }
          else if(irBuilder->getScope()->parent) 
            res = BinaryInst::CreateSdiv(context, lhs, rhs, irBuilder->getBasicBlock());
        }
				break;
			case BinaryOp::MOD:
          if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(rhs)) {
            res = ConstantInt::get(context, context.Int32Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() % dynamic_cast<ConstantInt*>(rhs)->getValue());
          }
          else if(irBuilder->getScope()->parent) 
            res = BinaryInst::CreateMod(context, lhs, rhs, irBuilder->getBasicBlock());
				break;
			case BinaryOp::LT:
        if(is_float) {
          if(irBuilder->getScope()->parent) 
            res = FcmpInst::Create(context, FcmpInst::FcmpOp::LT, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() < dynamic_cast<ConstantFloat*>(rhs)->getValue());
        } else {
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
        } else {
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
        } else {
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
        } else {
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
        } else {
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
        } else {
          if(irBuilder->getScope()->parent) 
            res = IcmpInst::Create(context, IcmpInst::IcmpOp::NEQ, lhs, rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() != dynamic_cast<ConstantInt*>(rhs)->getValue());
        } 
        break;
			case BinaryOp::AND:{
          auto lb = BasicBlock::Create(context, "l", irBuilder->getFunction());
          auto rb = BasicBlock::Create(context, "r", irBuilder->getFunction());
          rb->addSuccessor(irBuilder->getNextBlock());
          BranchInst::Create(context, irBuilder->getNextBlock(), rb);
          irBuilder->setLoopBlock(lb, irBuilder->getNextBlock());
          lhs_->generate(irBuilder);
          lhs = irBuilder->getTmpVal();
          if (lhs != nullptr) {
            if (lhs->getType()->isIntegerType()){
              lhs = IcmpInst::Create(context, IcmpInst::IcmpOp::NEQ, lhs, ConstantZero::get(context, lhs->getType()), irBuilder->getBasicBlock());
            } else {
              lhs = FcmpInst::Create(context, FcmpInst::FcmpOp::NEQ, lhs, ConstantZero::get(context, lhs->getType()), irBuilder->getBasicBlock());
            }
            irBuilder->getBasicBlock()->addSuccessor(lb);
            irBuilder->getBasicBlock()->addSuccessor(rb);
            BranchInst::Create(context, lhs, lb, rb, irBuilder->getBasicBlock());
          }
          irBuilder->setBasicBlock(lb);
          rhs_->generate(irBuilder);
          rhs = irBuilder->getTmpVal();
          if (rhs != nullptr){
            if (rhs->getType()->isIntegerType()){
              rhs = IcmpInst::Create(context, IcmpInst::IcmpOp::NEQ, rhs, ConstantZero::get(context, rhs->getType()), irBuilder->getBasicBlock());
            } else {
              rhs = FcmpInst::Create(context, FcmpInst::FcmpOp::NEQ, rhs, ConstantZero::get(context, rhs->getType()), irBuilder->getBasicBlock());
            }
            irBuilder->getBasicBlock()->addSuccessor(irBuilder->getWhileBlock());
            irBuilder->getBasicBlock()->addSuccessor(rb);
            BranchInst::Create(context, rhs, irBuilder->getWhileBlock(), rb, irBuilder->getBasicBlock());
          }
          irBuilder->setBasicBlock(lb);
          irBuilder->popLoopBlock();
        }
        break;
			case BinaryOp::OR: {
          auto lb = BasicBlock::Create(context, "l", irBuilder->getFunction());
          auto rb = BasicBlock::Create(context, "r", irBuilder->getFunction());
          lb->addSuccessor(irBuilder->getWhileBlock());
          BranchInst::Create(context, irBuilder->getWhileBlock(), lb);
          irBuilder->setLoopBlock(irBuilder->getWhileBlock(), rb);
          lhs_->generate(irBuilder);
          lhs = irBuilder->getTmpVal();
          if (lhs != nullptr) {
            if (lhs->getType()->isIntegerType()){
              lhs = IcmpInst::Create(context, IcmpInst::IcmpOp::NEQ, lhs, ConstantZero::get(context, lhs->getType()), irBuilder->getBasicBlock());
            } else {
              lhs = FcmpInst::Create(context, FcmpInst::FcmpOp::NEQ, lhs, ConstantZero::get(context, lhs->getType()), irBuilder->getBasicBlock());
            }
            irBuilder->getBasicBlock()->addSuccessor(lb);
            irBuilder->getBasicBlock()->addSuccessor(rb);
            BranchInst::Create(context, lhs, lb, rb, irBuilder->getBasicBlock());

          }
          irBuilder->setBasicBlock(rb);
          rhs_->generate(irBuilder);
          rhs = irBuilder->getTmpVal();
          if (rhs != nullptr){
            if (rhs->getType()->isIntegerType()){
              rhs = IcmpInst::Create(context, IcmpInst::IcmpOp::NEQ, rhs, ConstantZero::get(context, rhs->getType()), irBuilder->getBasicBlock());
            } else {
              rhs = FcmpInst::Create(context, FcmpInst::FcmpOp::NEQ, rhs, ConstantZero::get(context, rhs->getType()), irBuilder->getBasicBlock());
            }
            irBuilder->getBasicBlock()->addSuccessor(lb);
            irBuilder->getBasicBlock()->addSuccessor(irBuilder->getNextBlock());
            BranchInst::Create(context, rhs, lb, irBuilder->getNextBlock(), irBuilder->getBasicBlock());
          }
          irBuilder->setBasicBlock(rb);
          irBuilder->popLoopBlock();
        }
        break;
      default: break;
		}
    irBuilder->setTmpVal(res);
}

void UnaryExpression::generate(IRBuilder *irBuilder) {
  Context &context = irBuilder->getContext();
  rhs_->generate(irBuilder);
  Value *rhs = irBuilder->getTmpVal(), *res = nullptr;
  if (rhs->getType()->isPointerType()) {
    if (dynamic_cast<GlobalVariable*>(rhs) && dynamic_cast<GlobalVariable*>(rhs)->isConst() ) {
      rhs = dynamic_cast<GlobalVariable*>(rhs)->getInitValue();
    } else if (irBuilder->getScope()->inGlobal()) {
      rhs = dynamic_cast<GlobalVariable*>(rhs)->getInitValue();
    } else {
      rhs = LoadInst::Create(context, rhs->getType()->getPtrElementType(), rhs, irBuilder->getBasicBlock());
    }
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
            res = BinaryInst::CreateSub(context, ConstantInt::get(context, rhs->getType(), 0), rhs, irBuilder->getBasicBlock());
          else 
            res = ConstantInt::get(context, context.Int32Type, -dynamic_cast<ConstantInt*>(rhs)->getValue());
        }
        break;
			case UnaryOp::NOT:
        if(irBuilder->getScope()->parent) {
          auto zero = ConstantZero::get(context, rhs->getType());
          rhs = IcmpInst::Create(context, 
                                 IcmpInst::IcmpOp::NEQ, 
                                 rhs, 
                                 zero, 
                                 irBuilder->getBasicBlock());
          zero = ConstantZero::get(context, rhs->getType());
          res = IcmpInst::Create(context, 
                                 IcmpInst::IcmpOp::EQ, 
                                 rhs, 
                                 zero, 
                                 irBuilder->getBasicBlock());
        }
        else
          res = ConstantInt::get(context, context.Int1Type, !(dynamic_cast<ConstantInt*>(rhs)->getValue()));
        break;
      case UnaryOp::POSITIVE:
        res = rhs;
        break;
      default:
        break;
	}
  irBuilder->setTmpVal(res);
}

void LValExpression::generate(IRBuilder *irBuilder) {
  Context &context = irBuilder->getContext();
  Scope *scope = irBuilder->getScope();
  if (irBuilder->getScope()->inGlobal()) {
    if(identifier_->dimension_.empty()) {
      auto val = scope->DeclIR[identifier_->id_];
      irBuilder->setTmpVal(val);
    } else {
      auto tmp = scope->DeclIR[identifier_->id_];
      auto arr = dynamic_cast<ConstantArray*>(dynamic_cast<GlobalVariable*>(tmp)->getInitValue());
      vector<int> indice;
      for(auto& idx : identifier_->dimension_) {
        idx->generate(irBuilder);
        auto temp = irBuilder->getTmpVal();
        if (dynamic_cast<GlobalVariable*>(temp)) {
          temp = dynamic_cast<GlobalVariable*>(temp)->getInitValue();
        }
        if (!temp->getType()->isIntegerType()) {
          throw Exception("array dimension isn't float in global");
        }
        indice.emplace_back(dynamic_cast<ConstantInt*>(temp)->getValue());
      }
      int len = arr->dimension_.size(), leng = indice.size(), acc = 1, idx = 0;
      //calculate the location of the multi-dimensions element
      for(int u = leng - 1; u >= 0; u--) {
        idx += acc * indice[u];
        acc *= arr->dimension_[u];
      }
      irBuilder->setTmpVal(arr->getElementValue(idx));
    }
  } else {
    Value *ptr = find_symbol(scope, identifier_->id_, true);
    if (dynamic_cast<GlobalVariable*>(ptr) && dynamic_cast<GlobalVariable*>(ptr)->isConst()) {
      if(identifier_->dimension_.empty()) {
        irBuilder->setTmpVal(ptr);
      } else {
        auto arr = dynamic_cast<ConstantArray*>(dynamic_cast<GlobalVariable*>(ptr)->getInitValue());
        vector<int> indice;
        for(auto& idx : identifier_->dimension_) {
          idx->generate(irBuilder);
          auto temp = irBuilder->getTmpVal();
          if (dynamic_cast<GlobalVariable*>(temp)) {
            temp = dynamic_cast<GlobalVariable*>(temp)->getInitValue();
          }
          if (!temp->getType()->isIntegerType()) {
            throw Exception("array dimension isn't float in global");
          }
          indice.emplace_back(dynamic_cast<ConstantInt*>(temp)->getValue());
        }
        int len = arr->dimension_.size(), leng = indice.size(), acc = 1, idx = 0;
        //calculate the location of the multi-dimensions element
        for(int u = leng - 1; u >= 0; u--) {
          idx += acc * indice[u];
          acc *= arr->dimension_[u];
        }
        irBuilder->setTmpVal(arr->getElementValue(idx));
      }
    } else {
      if (dynamic_cast<Constant*>(ptr)) {
        if (dynamic_cast<ConstantArray*>(ptr)) {
          auto arr = dynamic_cast<ConstantArray*>(ptr);
          vector<int> indice;
          for(auto& idx : identifier_->dimension_) {
            idx->generate(irBuilder);
            auto temp = irBuilder->getTmpVal();
            if (dynamic_cast<GlobalVariable*>(temp)) {
              temp = dynamic_cast<GlobalVariable*>(temp)->getInitValue();
            }
            if (!temp->getType()->isIntegerType()) {
              throw Exception("array dimension isn't float in global");
            }
            indice.emplace_back(dynamic_cast<ConstantInt*>(temp)->getValue());
          }
          int len = arr->dimension_.size(), leng = indice.size(), acc = 1, idx = 0;
          //calculate the location of the multi-dimensions element
          for(int u = leng - 1; u >= 0; u--) {
            idx += acc * indice[u];
            acc *= arr->dimension_[u];
          }
          ptr = arr->getElementValue(idx);
        }
      } else {      
        bool fun_arr_ptr = false;
        if (ptr->getType()->isPointerType() && ptr->getType()->getPtrElementType()->isPointerType()) {
          ptr = LoadInst::Create(context, ptr, irBuilder->getBasicBlock());
          cout << ptr->print() << endl;
          fun_arr_ptr = true;
        }
        if(!(identifier_->dimension_.empty())){
          vector<Value *> idxList;
          int size = identifier_->dimension_.size();
          for (int i = 0; i < size; i++) {
            auto idx = identifier_->dimension_[i];
            idx->generate(irBuilder);
            auto tmp = irBuilder->getTmpVal();
            if (tmp->getType()->isFloatType()) {
              throw Exception("array dimension isn't float in Function " + irBuilder->getFunction()->getName());
            } else if (tmp->getType()->isPointerType()) {
              tmp = LoadInst::Create(context, tmp, irBuilder->getBasicBlock());
            }
            idxList.emplace_back(tmp);
            if (fun_arr_ptr && i == 0) {
              ptr = GetElementPtrInst::Create(context, ptr, idxList, irBuilder->getBasicBlock());
              idxList.pop_back();
            }
          }
          idxList.insert(idxList.begin(), ConstantInt::get(context, context.Int32Type, 0));
          ptr = GetElementPtrInst::Create(context, 
                                          ptr, 
                                          idxList,
                                          irBuilder->getBasicBlock());
        }
      }
      irBuilder->setTmpVal(ptr);
    }
  }
}

void Block::generate(IRBuilder *irBuilder) {
  irBuilder->setScope(scope_);
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
  if (rval->getType()->isPointerType()) {
    rval = LoadInst::Create(irBuilder->getContext(), rval, irBuilder->getBasicBlock());
  }
  StoreInst::Create(irBuilder->getContext(), rval, lval, irBuilder->getBasicBlock());
}

void IfElseStatement::generate(IRBuilder *irBuilder) {
  Context &c = irBuilder->getContext();
  irBuilder->setScope(scope_);
  auto true_bb =
      BasicBlock::Create(c, "if_true_entry", irBuilder->getFunction());
  auto false_bb =
      BasicBlock::Create(c, "if_false_entry", irBuilder->getFunction());
  auto next_bb = BasicBlock::Create(c, "next_entry", irBuilder->getFunction());
  true_bb->addSuccessor(next_bb);
  false_bb->addSuccessor(next_bb);
  if (elseStmt_) {
    irBuilder->setLoopBlock(true_bb, false_bb);  
  } else {
    irBuilder->setLoopBlock(true_bb, next_bb);
  }
  cond_->generate(irBuilder);
  irBuilder->popLoopBlock();
  auto tmpVal = irBuilder->getTmpVal();
  if (tmpVal) {
    if (tmpVal->getType()->isPointerType()) {
      tmpVal = LoadInst::Create(c,tmpVal,irBuilder->getBasicBlock());
    }
    Value *condVal;
    if (tmpVal->getType()->isIntegerType()) {
      if (static_cast<IntegerType*>(tmpVal->getType())->getBitsNum() != 1) {    
        condVal = IcmpInst::Create(c, IcmpInst::IcmpOp::NEQ, tmpVal,
                                  ConstantInt::get(c, tmpVal->getType(), 0),
                                  irBuilder->getBasicBlock());
      } else {
        condVal = tmpVal;
      }
    } else {
      condVal =
          IcmpInst::Create(c, IcmpInst::IcmpOp::NEQ, tmpVal,
                          ConstantFloat::get(c, 0), irBuilder->getBasicBlock());
    }
    if (elseStmt_) {
      irBuilder->getBasicBlock()->addSuccessor(true_bb);
      irBuilder->getBasicBlock()->addSuccessor(false_bb);
      BranchInst::Create(c, condVal, true_bb, false_bb,
                        irBuilder->getBasicBlock());
    } else {
      irBuilder->getBasicBlock()->addSuccessor(true_bb);
      irBuilder->getBasicBlock()->addSuccessor(next_bb);
      BranchInst::Create(c, condVal, true_bb, next_bb,
                        irBuilder->getBasicBlock());
    }
  }
  irBuilder->setBasicBlock(true_bb);
  thenStmt_->generate(irBuilder);
  if (!irBuilder->getBasicBlock()->hasTerminator()) {
    irBuilder->getBasicBlock()->addSuccessor(next_bb);
    BranchInst::Create(c, next_bb, irBuilder->getBasicBlock());
  }
  if (elseStmt_) {
    irBuilder->setBasicBlock(false_bb);
    elseStmt_->generate(irBuilder);
    if (!irBuilder->getBasicBlock()->hasTerminator()) {
      irBuilder->getBasicBlock()->addSuccessor(next_bb);
      BranchInst::Create(c, next_bb, irBuilder->getBasicBlock());
    }
  } else {
    false_bb->eraseFromParent();
  }
  irBuilder->setBasicBlock(next_bb);
  irBuilder->setScope(scope_->parent);
}

void WhileStatement::generate(IRBuilder *irBuilder) {
  Context& c = irBuilder->getContext();
  irBuilder->setScope(scope_);
  auto while_bb = BasicBlock::Create(c, "while_entry", irBuilder->getFunction());
  auto next_bb = BasicBlock::Create(c, "next_entry", irBuilder->getFunction());
  while_bb->addSuccessor(next_bb);
  irBuilder->setLoopBlock(while_bb, next_bb);
  cond_->generate(irBuilder);
  irBuilder->popLoopBlock();
  auto tmpVal = irBuilder->getTmpVal();
  if (tmpVal) {
    if (tmpVal->getType()->isPointerType()) {
      tmpVal = LoadInst::Create(c,tmpVal,irBuilder->getBasicBlock());
    }    
    Value* condVal;
    if (tmpVal->getType()->isIntegerType()) {
      condVal = IcmpInst::Create(
          c, IcmpInst::IcmpOp::NEQ, tmpVal,
          ConstantInt::get(c, tmpVal->getType(), 0),
          irBuilder->getBasicBlock());
    } else {
      condVal = IcmpInst::Create(c, IcmpInst::IcmpOp::NEQ, tmpVal,
                                ConstantFloat::get(c, 0),
                                irBuilder->getBasicBlock());
    }
    irBuilder->getBasicBlock()->addSuccessor(while_bb);
    irBuilder->getBasicBlock()->addSuccessor(next_bb);
    BranchInst::Create(c, condVal, while_bb, next_bb, irBuilder->getBasicBlock());    
    irBuilder->setBasicBlock(while_bb);
    irBuilder->setLoopBlock(while_bb, next_bb);
    doStmt_->generate(irBuilder); 
    irBuilder->popLoopBlock();
    if (!irBuilder->getBasicBlock()->hasTerminator()) {
      irBuilder->getBasicBlock()->addSuccessor(while_bb);
      irBuilder->getBasicBlock()->addSuccessor(next_bb);
      BranchInst::Create(c, condVal, while_bb, next_bb, irBuilder->getBasicBlock());    
    }
  }
  irBuilder->setBasicBlock(next_bb);
  irBuilder->setScope(scope_->parent);
}

void ReturnStatement::generate(IRBuilder *irBuilder) {
  Context &c = irBuilder->getContext();
  Value *retVal;
  if (value_) {
    auto ret_type = irBuilder->getFunction()->getReturnType();
    value_->generate(irBuilder);
    retVal = irBuilder->getTmpVal();
    if (retVal->getType()->isPointerType()) {
      retVal = LoadInst::Create(c, retVal, irBuilder->getBasicBlock());
    }
    if (ret_type != retVal->getType()) {
      if (ret_type->isIntegerType()) {
        retVal =
            FpToSiInst::Create(c, Type::getInt32Type(c), retVal, irBuilder->getBasicBlock());
      } else {
        retVal =
            SiToFpInst::Create(c, Type::getFloatType(c), retVal, irBuilder->getBasicBlock());
      }
    }
    ReturnInst::Create(c, retVal, irBuilder->getBasicBlock());
  } else {
    ReturnInst::Create(c, irBuilder->getBasicBlock());
  }
}

void BreakStatement::generate(IRBuilder *irBuilder) {
  irBuilder->getBasicBlock()->addSuccessor(irBuilder->getNextBlock());
  BranchInst::Create(irBuilder->getContext(),irBuilder->getNextBlock(),irBuilder->getBasicBlock());
}

void ContinueStatement::generate(IRBuilder *irBuilder) {
  irBuilder->getBasicBlock()->addSuccessor(irBuilder->getWhileBlock());
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
    if (val->getType()->isPointerType() && !val->getType()->getPtrElementType()->isArrayType()) {
      val = LoadInst::Create(context, val, irBuilder->getBasicBlock());
    }
    if(dynamic_cast<ConstantInt*>(val) && funcType->getArgumentType(u) == context.FloatType)
      //SiToFpInst::Create(context, context.FloatType, val, irBuilder->getBasicBlock()); godbolt transform number without explicit instructions
      funcArgs.emplace_back(ConstantFloat::get(context, static_cast<float>(dynamic_cast<ConstantInt*>(val)->getValue())));
    else if(dynamic_cast<ConstantFloat*>(val) && funcType->getArgumentType(u) != context.FloatType) 
      funcArgs.emplace_back(ConstantInt::get(context, 
                                             funcType->getArgumentType(u),
                                             static_cast<int>(dynamic_cast<ConstantFloat*>(val)->getValue())));
    else funcArgs.emplace_back(val);
  }
  auto tmp = CallInst::Create(context, dynamic_cast<Function*>(irBuilder->getModule()->symbolTable_[identifier_->id_]),
                   funcArgs, 
                   irBuilder->getBasicBlock());
  irBuilder->setTmpVal(tmp);
  //return value will be set by ReturnStatement::generate
} 
