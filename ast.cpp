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
bool force_trans(IRBuilder *irBuilder, Value*& lhs, Value*& rhs) {
  bool is_global = irBuilder->getScope()->inGlobal();
  bool is_float = lhs->getType()->isFloatType() || rhs->getType()->isFloatType();
  Context &context =irBuilder->getContext();
  if(is_float) {
    if(is_global) {
      if(auto tmp = dynamic_cast<ConstantInt*>(lhs)) {
        // whether we need to delete the old constantInt
        //e.g. delete lhs;
        lhs = new ConstantFloat(context, context.FloatType, tmp->getValue());
      } 
      if(auto tmp = dynamic_cast<ConstantInt*>(rhs)) {
        rhs = new ConstantFloat(context, context.FloatType, tmp->getValue());
      }
    } 
    else {
      if(lhs->getType()->isIntegerType()) 
          lhs = SiToFpInst::Create(context, context.FloatType, lhs, irBuilder->getBasicBlock());
      if(rhs->getType()->isIntegerType()) 
          rhs = SiToFpInst::Create(context, context.FloatType, rhs, irBuilder->getBasicBlock());
    }
  }
  return is_float;
}

void parse_nest_array(vector<Value *>&ans, ArrayValue *cur, int idx, vector<int>&nums, bool isInt, int& offset, IRBuilder *irBuilder){
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
      offset = ans.size();
    }
    else {
      if(cnt) {
        ans.resize(ans.size() + remain - cnt, ConstantZero::get(context, isInt ? context.Int32Type : context.FloatType));
        cnt = 0;
      }
      parse_nest_array(ans, val, idx + 1, nums, isInt, offset, irBuilder);
    }
  }

  if(ans.size()-original<expect) {
    ans.resize(expect + original, ConstantZero::get(context, isInt ? context.Int32Type : context.FloatType));
  }
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
  auto funty = FunctionType::get(returnType, argsType);
  string parms[10]; 
  for (int i = 0; i < argsType.size(); i++) {
    parms[i] = "i";
  }
  auto fl = new FormalArgumentList();
  string *s = new string("i");
  auto id = new Identifier(s);
  fl->list_.emplace_back(new FormalArgument(SysType::INT,id));
  string *s2 = new string(name);
  auto id2 = new Identifier(s);
  FunctionDefinition* fde = new FunctionDefinition(SysType::VOID,id2,fl, nullptr);
  auto x = Function::Create(c, funty, parms, name, irBuilder->getModule(), true, true);
  scope_->funcIR[fde] = x;
}

void Root::generate(IRBuilder *irBuilder) {
  Context&c = irBuilder->getContext();
  irBuilder->setScope(scope_);
  addLibFn(irBuilder, "putint" , scope_, Type::getVoidType(c),{Type::getInt32Type(c)});
  addLibFn(irBuilder, "putfloat" , scope_, Type::getVoidType(c),{Type::getFloatType(c)});
  addLibFn(irBuilder, "putch" , scope_, Type::getVoidType(c),{Type::getInt32Type(c)});
  addLibFn(irBuilder, "putarray" , scope_, Type::getVoidType(c),{Type::getInt32Type(c), PointerType::get(c,c.Int32Type)});
  addLibFn(irBuilder, "putfarray" , scope_, Type::getVoidType(c),{Type::getInt32Type(c), PointerType::get(c,c.FloatType)});
  addLibFn(irBuilder, "getint" , scope_, Type::getInt32Type(c),{});
  addLibFn(irBuilder, "getfloat" , scope_, Type::getFloatType(c),{});
  addLibFn(irBuilder, "getch" , scope_, Type::getInt32Type(c),{});
  addLibFn(irBuilder, "getarray" , scope_, Type::getInt32Type(c),{PointerType::get(c, c.Int32Type)});
  addLibFn(irBuilder, "getfarray" , scope_, Type::getInt32Type(c),{PointerType::get(c, c.FloatType)});
  addLibFn(irBuilder, "memset" , scope_, Type::getPtrType(c, c.VoidType),{PointerType::get(c, c.VoidType), Type::getInt32Type(c), Type::getInt32Type(c)});
  addLibFn(irBuilder, "_sysy_starttime" , scope_, Type::getInt32Type(c),{});
  addLibFn(irBuilder, "_sysy_stoptime" , scope_, Type::getInt32Type(c),{});
  for (auto &decl : this->declareStatement_) {
    decl->generate(irBuilder);
  }

  for (auto &funcDef : this->functionDefinitions_) {
    irBuilder->setScope(scope_);
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
      if (val->getType()->isIntegerType()) {
        int32_t init_val = dynamic_cast<ConstantInt *>(val)->getValue();
        if (type_ == SysType::INT) {
          constant = new ConstantInt(context, context.Int32Type, init_val);
        } else {
          constant = new ConstantFloat(context, context.FloatType, init_val);
        }
      } else {
        float init_val = dynamic_cast<ConstantFloat *>(val)->getValue();
        if (type_ == SysType::INT) {
          constant = new ConstantInt(context, context.Int32Type, init_val);
        } else {
          constant = new ConstantFloat(context, context.FloatType, init_val);
        }
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
  int offset = 0;
  if(value_) {
      parse_nest_array(vals, value_, 0, nums, type_ == SysType::INT, offset, irBuilder);
  } 
  else 
    vals.resize(total, ConstantZero::get(context, type));

  if(irBuilder->getScope()->inGlobal()) {
    value = GlobalVariable::Create(context, arrType, identifier_->id_, isConst_,
                                   ConstantArray::get(context, arrType, vals, dimensions),
                                   irBuilder->getModule());
  } else {
    if (isConst_) {
      AllocaInst::Create(context, arrType, irBuilder->getBasicBlock());
      value = ConstantArray::get(context, arrType, vals, dimensions);
    } else {
      BasicBlock *bb = irBuilder->getBasicBlock();
      value = AllocaInst::Create(context, arrType, irBuilder->getBasicBlock());
      if (value_) {
        if (offset != total && (type->isIntegerType() || type->isFloatType())) {
          auto func = dynamic_cast<Function*>(irBuilder->getModule()->symbolTable_["memset"]);
          vector<Value*> idxList;
          for (int i = 0; i < len + 1; i++) {
            idxList.emplace_back(ConstantInt::get(context, context.Int32Type,0));
          }
          auto gep_tmp = GetElementPtrInst::Create(context, value, idxList, bb);
          auto tmp = CallInst::Create(context, func, 
            { gep_tmp,  ConstantInt::get(context, context.Int32Type,0), ConstantInt::get(context, context.Int32Type, total * 4)}, irBuilder->getBasicBlock());
        }
        vector<Value*> idxList;
        for (int i = 0; i < len; i++) {
          idxList.emplace_back(ConstantInt::get(context, context.Int32Type,0));
        }
        // TODO : call the memset function in C
        Value* tmp;
        for(int u = 0; u < offset; u++) {
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
          auto tmp = irBuilder->getTmpVal();
          if (dynamic_cast<GlobalVariable*>(tmp)) {
            if (!dynamic_cast<GlobalVariable*>(tmp)->isConst()) {
              throw Exception("array dimension is not const");    
            }
            tmp = dynamic_cast<GlobalVariable*>(tmp)->getInitValue();
          } else if (!dynamic_cast<ConstantInt*>(tmp)) {
              throw Exception("array dimension is not const");    
          }
          dimension.emplace_back(dynamic_cast<ConstantInt *>(tmp)->getValue());
        }
      }
      if (dimension.size() != 0) {
        // argsType.emplace_back(context,
        //     ArrayType::get(context, check_sys_type(arg->type_, context),
        //                    dimension));
        argsType.emplace_back(PointerType::get(context,
            ArrayType::get(context, check_sys_type(arg->type_, context),
                           dimension)));
      } else {
        // argsType.emplace_back(ArrayType::get(context, check_sys_type(arg->type_, context), -1));
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
  switch(op_) {
			case BinaryOp::ADD:
				if(is_float) {
          if (dynamic_cast<ConstantFloat*>(lhs) && dynamic_cast<ConstantFloat*>(rhs)) {
            res = ConstantFloat::get(context, 
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() + dynamic_cast<ConstantFloat*>(rhs)->getValue());
          } else {
            if (dynamic_cast<ConstantFloat*>(lhs) && dynamic_cast<ConstantFloat*>(lhs)->getValue() == 0) {
              res = rhs;
            } else if (dynamic_cast<ConstantFloat*>(rhs) && dynamic_cast<ConstantFloat*>(rhs)->getValue() == 0) {
              res = lhs;
            } else {
              res = BinaryInst::CreateFadd(context, lhs, rhs, irBuilder->getBasicBlock());
            }
          }
        } else {
          if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(rhs)) {
            res = ConstantInt::get(context, context.Int32Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() + dynamic_cast<ConstantInt*>(rhs)->getValue());
          } else {
            if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(lhs)->getValue() == 0) {
              res = rhs;
            } else if (dynamic_cast<ConstantInt*>(rhs) && dynamic_cast<ConstantInt*>(rhs)->getValue() == 0) {
              res = lhs;
            } else {
              res = BinaryInst::CreateAdd(context, lhs, rhs, irBuilder->getBasicBlock());
            }
          }
        }
				break;
			case BinaryOp::SUB:
				if(is_float) {
          if (dynamic_cast<ConstantFloat*>(lhs) && dynamic_cast<ConstantFloat*>(rhs)) {
            res = ConstantFloat::get(context, 
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() - dynamic_cast<ConstantFloat*>(rhs)->getValue());
          } else {
            if (dynamic_cast<ConstantFloat*>(lhs) && dynamic_cast<ConstantFloat*>(lhs)->getValue() == 0) {
              res = UnaryInst::CreateNegative(context, rhs, irBuilder->getBasicBlock());
            } else if (dynamic_cast<ConstantFloat*>(rhs) && dynamic_cast<ConstantFloat*>(rhs)->getValue() == 0) {
              res = lhs;
            } else {
              res = BinaryInst::CreateFsub(context, lhs, rhs, irBuilder->getBasicBlock());
            }
          }
        } else {
          if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(rhs)) {
            res = ConstantInt::get(context, context.Int32Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() - dynamic_cast<ConstantInt*>(rhs)->getValue());
          }
          else {
            if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(lhs)->getValue() == 0) {
              res = UnaryInst::CreateNegative(context, rhs, irBuilder->getBasicBlock());
            } else if (dynamic_cast<ConstantInt*>(rhs) && dynamic_cast<ConstantInt*>(rhs)->getValue() == 0) {
              res = lhs;
            } else { 
              res = BinaryInst::CreateSub(context, lhs, rhs, irBuilder->getBasicBlock());
            }
          } 
        }
				break;
			case BinaryOp::MUL:
				if(is_float) {
          if (dynamic_cast<ConstantFloat*>(lhs) && dynamic_cast<ConstantFloat*>(rhs)) {
            res = ConstantFloat::get(context, 
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() * dynamic_cast<ConstantFloat*>(rhs)->getValue());
          } else {
            if (dynamic_cast<ConstantFloat*>(lhs) && dynamic_cast<ConstantFloat*>(lhs)->getValue() == 1) {
              res = rhs;
            } else if (dynamic_cast<ConstantFloat*>(rhs) && dynamic_cast<ConstantFloat*>(rhs)->getValue() == 1) {
              res = lhs;
            } else {
              res = BinaryInst::CreateFmul(context, lhs, rhs, irBuilder->getBasicBlock());
            }
          }
        } else {
          if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(rhs)) {
            res = ConstantInt::get(context, context.Int32Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() * dynamic_cast<ConstantInt*>(rhs)->getValue());
          } else {
            if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(lhs)->getValue() == 1) {
              res = rhs;
            } else if (dynamic_cast<ConstantInt*>(rhs) && dynamic_cast<ConstantInt*>(rhs)->getValue() == 1) {
              res = lhs;
            } else { 
              res = BinaryInst::CreateMul(context, lhs, rhs, irBuilder->getBasicBlock());
            }
          }
        }
				break;
			case BinaryOp::DIV:
				if(is_float) {
          if (dynamic_cast<ConstantFloat*>(lhs) && dynamic_cast<ConstantFloat*>(rhs)) {
            res = ConstantFloat::get(context, 
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() / dynamic_cast<ConstantFloat*>(rhs)->getValue());
          } else {
            if (dynamic_cast<ConstantFloat*>(rhs) && dynamic_cast<ConstantFloat*>(rhs)->getValue() == 1) {
              res = lhs;
            } else { 
              res = BinaryInst::CreateFdiv(context, lhs, rhs, irBuilder->getBasicBlock());
            }
          }
        } else {
          if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(rhs)) {
            res = ConstantInt::get(context, context.Int32Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() / dynamic_cast<ConstantInt*>(rhs)->getValue());
          } else {
            if (dynamic_cast<ConstantInt*>(rhs) && dynamic_cast<ConstantInt*>(rhs)->getValue() == 1) {
              res = lhs;
            } else { 
              res = BinaryInst::CreateSdiv(context, lhs, rhs, irBuilder->getBasicBlock());
            }
          } 
        }
				break;
			case BinaryOp::MOD:
          if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(rhs)) {
            res = ConstantInt::get(context, context.Int32Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() % dynamic_cast<ConstantInt*>(rhs)->getValue());
          } else {
            if (dynamic_cast<ConstantInt*>(rhs) && dynamic_cast<ConstantInt*>(rhs)->getValue() == 1) {
              res = ConstantInt::get(context, context.Int32Type, 0);
            } else {
              res = BinaryInst::CreateMod(context, lhs, rhs, irBuilder->getBasicBlock());
            }
          } 
				break;
			case BinaryOp::LT:
        if(is_float) {
          if (dynamic_cast<ConstantFloat*>(lhs) && dynamic_cast<ConstantFloat*>(rhs)) {
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() < dynamic_cast<ConstantFloat*>(rhs)->getValue());
          } else {
            res = FcmpInst::Create(context, FcmpInst::FcmpOp::LT, lhs, rhs, irBuilder->getBasicBlock());
          }
        } else {
          if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(rhs)) {
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() < dynamic_cast<ConstantInt*>(rhs)->getValue());
          } else {
            res = IcmpInst::Create(context, IcmpInst::IcmpOp::LT, lhs, rhs, irBuilder->getBasicBlock());
          }
        }
        break;
			case BinaryOp::LTE:
        if(is_float) {
          if (dynamic_cast<ConstantFloat*>(lhs) && dynamic_cast<ConstantFloat*>(rhs)) {
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() <= dynamic_cast<ConstantFloat*>(rhs)->getValue());
          } else {
            res = FcmpInst::Create(context, FcmpInst::FcmpOp::LTE, lhs, rhs, irBuilder->getBasicBlock());
          }
        } else {
          if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(rhs)) {
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() <= dynamic_cast<ConstantInt*>(rhs)->getValue());
          } else {            
            res = IcmpInst::Create(context, IcmpInst::IcmpOp::LTE, lhs, rhs, irBuilder->getBasicBlock());
          }
        }
        break;
			case BinaryOp::GT:
        if(is_float) {
          if (dynamic_cast<ConstantFloat*>(lhs) && dynamic_cast<ConstantFloat*>(rhs)) {
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() > dynamic_cast<ConstantFloat*>(rhs)->getValue());
          } else {            
            res = FcmpInst::Create(context, FcmpInst::FcmpOp::GT, lhs, rhs, irBuilder->getBasicBlock());
          }
        } else {
          if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(rhs)) {
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() > dynamic_cast<ConstantInt*>(rhs)->getValue());
          } else {            
            res = IcmpInst::Create(context, IcmpInst::IcmpOp::GT, lhs, rhs, irBuilder->getBasicBlock());
          }
        } 
        break;
			case BinaryOp::GTE:
        if(is_float) {
          if (dynamic_cast<ConstantFloat*>(lhs) && dynamic_cast<ConstantFloat*>(rhs)) {
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() >= dynamic_cast<ConstantFloat*>(rhs)->getValue());
          } else {            
            res = FcmpInst::Create(context, FcmpInst::FcmpOp::GTE, lhs, rhs, irBuilder->getBasicBlock());
          }
        } else {
          if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(rhs)) {
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() >= dynamic_cast<ConstantInt*>(rhs)->getValue());
          } else {
            res = IcmpInst::Create(context, IcmpInst::IcmpOp::GTE, lhs, rhs, irBuilder->getBasicBlock());            
          }
        } 
        break;
			case BinaryOp::EQ:
        if(is_float) {
          if (dynamic_cast<ConstantFloat*>(lhs) && dynamic_cast<ConstantFloat*>(rhs)) {
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() == dynamic_cast<ConstantFloat*>(rhs)->getValue());
          } else {            
            res = FcmpInst::Create(context, FcmpInst::FcmpOp::EQ, lhs, rhs, irBuilder->getBasicBlock());
          }
        } else {
          if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(rhs)) {
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() == dynamic_cast<ConstantInt*>(rhs)->getValue());
          } else {
            res = IcmpInst::Create(context, IcmpInst::IcmpOp::EQ, lhs, rhs, irBuilder->getBasicBlock());            
          }
        } 
        break;
			case BinaryOp::NEQ:
        if(is_float) {
          if (dynamic_cast<ConstantFloat*>(lhs) && dynamic_cast<ConstantFloat*>(rhs)) {
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantFloat*>(lhs)->getValue() != dynamic_cast<ConstantFloat*>(rhs)->getValue());
          } else {
            res = FcmpInst::Create(context, FcmpInst::FcmpOp::NEQ, lhs, rhs, irBuilder->getBasicBlock());            
          }
        } else {
          if (dynamic_cast<ConstantInt*>(lhs) && dynamic_cast<ConstantInt*>(rhs)) {
            res = ConstantInt::get(context, context.Int1Type,
                  dynamic_cast<ConstantInt*>(lhs)->getValue() != dynamic_cast<ConstantInt*>(rhs)->getValue());
          } else {
            res = IcmpInst::Create(context, IcmpInst::IcmpOp::NEQ, lhs, rhs, irBuilder->getBasicBlock());            
          }
        } 
        break;
			case BinaryOp::AND:{
          auto lb = BasicBlock::Create(context, "l", irBuilder->getFunction());
          auto rb = BasicBlock::Create(context, "r", irBuilder->getFunction());
          rb->addSuccessor(irBuilder->getNextBlock());
          BranchInst::Create(context, irBuilder->getNextBlock(), rb);
          irBuilder->setLoopBlock(lb, irBuilder->getNextBlock());
          lhs_->generate(irBuilder);
          irBuilder->popLoopBlock();
          lhs = irBuilder->getTmpVal();
          if (lhs != nullptr) {
            if (lhs->getType()->isPointerType()) {
              lhs = LoadInst::Create(context, lhs, irBuilder->getBasicBlock());
            }
            irBuilder->getBasicBlock()->addSuccessor(lb);
            irBuilder->getBasicBlock()->addSuccessor(rb);
            BranchInst::Create(context, lhs, lb, rb, irBuilder->getBasicBlock());
          }
          irBuilder->setBasicBlock(lb);
          rhs_->generate(irBuilder);
          rhs = irBuilder->getTmpVal();
          if (rhs != nullptr){
            if (rhs->getType()->isPointerType()) {
              rhs = LoadInst::Create(context, rhs, irBuilder->getBasicBlock());
            }
            irBuilder->getBasicBlock()->addSuccessor(irBuilder->getWhileBlock());
            irBuilder->getBasicBlock()->addSuccessor(rb);
            BranchInst::Create(context, rhs, irBuilder->getWhileBlock(), rb, irBuilder->getBasicBlock());
          }
          irBuilder->setBasicBlock(lb);
        }
        break;
			case BinaryOp::OR: {
          auto lb = BasicBlock::Create(context, "l", irBuilder->getFunction());
          auto rb = BasicBlock::Create(context, "r", irBuilder->getFunction());
          lb->addSuccessor(irBuilder->getWhileBlock());
          BranchInst::Create(context, irBuilder->getWhileBlock(), lb);
          irBuilder->setLoopBlock(irBuilder->getWhileBlock(), rb);
          lhs_->generate(irBuilder);
          irBuilder->popLoopBlock();
          lhs = irBuilder->getTmpVal();
          if (lhs != nullptr) {
            if (lhs->getType()->isPointerType()) {
              lhs = LoadInst::Create(context, lhs, irBuilder->getBasicBlock());
            }
            irBuilder->getBasicBlock()->addSuccessor(lb);
            irBuilder->getBasicBlock()->addSuccessor(rb);
            BranchInst::Create(context, lhs, lb, rb, irBuilder->getBasicBlock());
          }
          irBuilder->setBasicBlock(rb);
          if (dynamic_cast<BinaryExpression*>(rhs_) && dynamic_cast<BinaryExpression*>(rhs_)->op_ == BinaryOp::AND){
            irBuilder->setLoopBlock(irBuilder->getWhileBlock(), irBuilder->getNextBlock());
          } else irBuilder->setLoopBlock(irBuilder->getWhileBlock(), rb);
          rhs_->generate(irBuilder);
          irBuilder->popLoopBlock();
          rhs = irBuilder->getTmpVal();
          if (rhs != nullptr){
            if (rhs->getType()->isPointerType()) {
              rhs = LoadInst::Create(context, rhs, irBuilder->getBasicBlock());
            }
            irBuilder->getBasicBlock()->addSuccessor(lb);
            irBuilder->getBasicBlock()->addSuccessor(irBuilder->getNextBlock());
            BranchInst::Create(context, rhs, lb, irBuilder->getNextBlock(), irBuilder->getBasicBlock());
          }
          irBuilder->setBasicBlock(rb);
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
          if (dynamic_cast<ConstantInt*>(rhs)) {
            res = ConstantFloat::get(context, -dynamic_cast<ConstantFloat*>(rhs)->getValue());          
          } else {
            if (dynamic_cast<Instruction*>(rhs) && dynamic_cast<Instruction*>(rhs)->isNegative()) {
              auto& inst_list = irBuilder->getBasicBlock()->instructionList_;
              inst_list.erase(--inst_list.end());
              res = dynamic_cast<Instruction*>(rhs)->getOperand(0);
            } else {
              if (dynamic_cast<ConstantFloat*>(rhs)) {
                res = ConstantFloat::get(context, -dynamic_cast<ConstantFloat*>(rhs)->getValue());
              } else {
                res = UnaryInst::CreateNegative(context, rhs, irBuilder->getBasicBlock());
              }
            }
          }
        } else {
          if (dynamic_cast<ConstantInt*>(rhs)) {
            res = ConstantInt::get(context, context.Int32Type, -dynamic_cast<ConstantInt*>(rhs)->getValue());          
          } else {
            if (dynamic_cast<Instruction*>(rhs) && dynamic_cast<Instruction*>(rhs)->isNegative()) {
              auto& inst_list = irBuilder->getBasicBlock()->instructionList_;
              inst_list.erase(--inst_list.end());
              res = dynamic_cast<Instruction*>(rhs)->getOperand(0);            
            } else {
              if (dynamic_cast<ConstantInt*>(rhs)) {
                res = ConstantInt::get(context, rhs->getType(), -dynamic_cast<ConstantInt*>(rhs)->getValue());
              } else {
                res = UnaryInst::CreateNegative(context, rhs, irBuilder->getBasicBlock());
              }
            }
          }
        }
        break;
			case UnaryOp::NOT:
        if (dynamic_cast<ConstantInt*>(rhs)) {
          res = ConstantInt::get(context, context.Int1Type, !(dynamic_cast<ConstantInt*>(rhs)->getValue()));          
        } else {
          if (dynamic_cast<Instruction*>(rhs) && dynamic_cast<Instruction*>(rhs)->isNot()) {
            auto& inst_list = irBuilder->getBasicBlock()->instructionList_;
            inst_list.erase(--inst_list.end());
            res = dynamic_cast<Instruction*>(rhs)->getOperand(0);
          } else {
            if (dynamic_cast<ConstantInt*>(rhs)) {
              res = ConstantInt::get(context, context.Int1Type, 
                      !(dynamic_cast<ConstantInt*>(rhs)->getValue()));
            } else {            
              res = UnaryInst::CreateNot(context, rhs, irBuilder->getBasicBlock());
            }         
          }
        }
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
    vector<Value*> indice;
    bool is_array = false;
    bool dimension_is_const = true;
    const int size = identifier_->dimension_.size();
    if (!identifier_->dimension_.empty()) {
        is_array = true;
        for (auto idx : identifier_->dimension_) {
          idx->generate(irBuilder);
          auto tmpVal = irBuilder->getTmpVal();
          if (dynamic_cast<GlobalVariable*>(tmpVal) && dynamic_cast<GlobalVariable*>(tmpVal)->isConst()) {
            tmpVal = dynamic_cast<GlobalVariable*>(tmpVal)->getInitValue();
          }
          if (tmpVal->getType()->isFloatType()) {
            throw Exception(string("array dimension isn't float ") + __FILE__ + to_string(__LINE__));
          }
          if (tmpVal->getType()->isPointerType()) {
            dimension_is_const = false;
            tmpVal = LoadInst::Create(context, tmpVal, irBuilder->getBasicBlock());
          } else if (!dynamic_cast<Constant*>(tmpVal)) {
            dimension_is_const = false;            
          }
          indice.emplace_back(tmpVal);
        }
    }
    bool is_func_array = false;
    if (ptr->getType()->isPointerType()) {
      if (ptr->getType()->getPtrElementType()->isPointerType()){
        is_array = true;
        is_func_array = true;
        ptr = LoadInst::Create(context, ptr, irBuilder->getBasicBlock());
      } else if (ptr->getType()->getPtrElementType()->isArrayType()){
        is_array = true;
      }
    }
    if (is_array) {
      if (dimension_is_const && size != 0) {
        ConstantArray* arr;
        bool is_const = false;
        if (dynamic_cast<GlobalVariable*>(ptr) && dynamic_cast<GlobalVariable*>(ptr)->isConst()) {
          is_const = true;
          arr = dynamic_cast<ConstantArray*>(dynamic_cast<GlobalVariable*>(ptr)->getInitValue());
        } else if (dynamic_cast<ConstantArray*>(ptr)) {
          is_const = true;
          arr = dynamic_cast<ConstantArray*>(ptr);
        }
        if (is_const) {        
          int len = arr->dimension_.size(), leng = indice.size(), acc = 1, idx = 0;
          for(int u = leng - 1; u >= 0; u--) {
            idx += acc * dynamic_cast<ConstantInt*>(indice[u])->getValue();
            acc *= arr->dimension_[u];
          }
          ptr = arr->getElementValue(idx);
        } else {
          if (size == 1) {
            if (is_func_array){
              ptr = GetElementPtrInst::Create(context, ptr, { *indice.begin() }, irBuilder->getBasicBlock());
            } else {
              ptr = GetElementPtrInst::Create(context, ptr, {ConstantInt::get(context, context.Int32Type, 0), *indice.begin() }, irBuilder->getBasicBlock());
            }
          } else if (size >= 2) {
            if (is_func_array) {
              // ptr = GetElementPtrInst::Create(context, ptr, { *indice.begin() }, irBuilder->getBasicBlock());
              // indice.erase(indice.begin());
              // indice.insert(indice.begin(), ConstantInt::get(context, context.Int32Type, 0));
              ptr = GetElementPtrInst::Create(context, 
                                      ptr, 
                                      indice,
                                      irBuilder->getBasicBlock());
            } else {
              indice.insert(indice.begin(), ConstantInt::get(context, context.Int32Type, 0));
              ptr = GetElementPtrInst::Create(context, 
                                      ptr, 
                                      indice,
                                      irBuilder->getBasicBlock());
            }
          }
        }
      } else {
        if (size == 0) {
          if (is_func_array){
            ptr = GetElementPtrInst::Create(context, ptr, {ConstantInt::get(context, context.Int32Type, 0)}, 
                      irBuilder->getBasicBlock());
          } else {
            ptr = GetElementPtrInst::Create(context, ptr, {
                  ConstantInt::get(context, context.Int32Type, 0),
                  ConstantInt::get(context, context.Int32Type, 0)}, 
                  irBuilder->getBasicBlock());
          }
        } else if (size == 1) {
          if (is_func_array){
            ptr = GetElementPtrInst::Create(context, ptr, { *indice.begin() }, irBuilder->getBasicBlock());
          } else {
            ptr = GetElementPtrInst::Create(context, ptr, {ConstantInt::get(context, context.Int32Type, 0), *indice.begin() }, irBuilder->getBasicBlock());
          }
        } else if (size >= 2) {
          if (is_func_array) {
            // ptr = GetElementPtrInst::Create(context, ptr, { *indice.begin() }, irBuilder->getBasicBlock());
            // indice.erase(indice.begin());
            // indice.insert(indice.begin(), ConstantInt::get(context, context.Int32Type, 0));
            ptr = GetElementPtrInst::Create(context, 
                                    ptr, 
                                    indice,
                                    irBuilder->getBasicBlock());
          } else {
            indice.insert(indice.begin(), ConstantInt::get(context, context.Int32Type, 0));
            ptr = GetElementPtrInst::Create(context, 
                                    ptr, 
                                    indice,
                                    irBuilder->getBasicBlock());
          }
        }
      }
    } else {
      bool is_const = false;
      if (dynamic_cast<GlobalVariable*>(ptr) && dynamic_cast<GlobalVariable*>(ptr)->isConst()) {
        is_const = true;
        ptr = dynamic_cast<GlobalVariable*>(ptr)->getInitValue();
      } else if (dynamic_cast<Constant*>(ptr)) {
        is_const = true;        
      }
    }
    irBuilder->setTmpVal(ptr);
  }
}

void Block::generate(IRBuilder *irBuilder) {
  irBuilder->setScope(scope_);
  for (auto& stateItem : statements_) {
    if (stateItem) {
      stateItem->generate(irBuilder);
    }
  }
  irBuilder->setScope(scope_->parent);
}

void DeclareStatement::generate(IRBuilder *irBuilder) {
  for (auto &declare_item : declares_) {
    declare_item->generate(irBuilder);
  }
}

void AssignStatement::generate(IRBuilder *irBuilder) {
  Context& c = irBuilder->getContext();
  lhs_->generate(irBuilder);
  auto lval = irBuilder->getTmpVal();
  rhs_->generate(irBuilder);
  auto rval = irBuilder->getTmpVal();
  if (rval->getType()->isPointerType()) {
    rval = LoadInst::Create(irBuilder->getContext(), rval, irBuilder->getBasicBlock());
  }
  if (lval->getType()->getPtrElementType() != rval->getType()){
    if (lval->getType()->getPtrElementType()->isIntegerType()){
      rval = FpToSiInst::Create(c, lval->getType()->getPtrElementType(), rval, irBuilder->getBasicBlock());
    } else if (lval->getType()->getPtrElementType()->isFloatType()){
      rval = SiToFpInst::Create(c, lval->getType()->getPtrElementType(), rval, irBuilder->getBasicBlock());    
    }
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
  auto next_bb = BasicBlock::Create(c, "if_next_entry", irBuilder->getFunction());
  // true_bb->addSuccessor(next_bb);
  if (elseStmt_) {
    // false_bb->addSuccessor(next_bb);
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
    if (!dynamic_cast<IcmpInst*>(tmpVal) && !dynamic_cast<FcmpInst*>(tmpVal)) {
      if (tmpVal->getType()->isIntegerType()) {
        condVal = IcmpInst::Create(c, IcmpInst::IcmpOp::NEQ, tmpVal,
                                  ConstantInt::get(c, tmpVal->getType(), 0),
                                  irBuilder->getBasicBlock());
      } else {
        condVal =
            FcmpInst::Create(c, FcmpInst::FcmpOp::NEQ, tmpVal,
                            ConstantFloat::get(c, 0), irBuilder->getBasicBlock());
      }
    } else {
      condVal = tmpVal;
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
  if (thenStmt_) {
    thenStmt_->generate(irBuilder);
  }
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
  // while_bb->addSuccessor(next_bb);
  irBuilder->setLoopBlock(while_bb, next_bb);
  cond_->generate(irBuilder);
  irBuilder->popLoopBlock();
  auto tmpVal = irBuilder->getTmpVal();
  if (tmpVal) {
    if (tmpVal->getType()->isPointerType()) {
      tmpVal = LoadInst::Create(c,tmpVal,irBuilder->getBasicBlock());
    }    
    Value* condVal;
    if (!dynamic_cast<IcmpInst*>(tmpVal) && !dynamic_cast<FcmpInst*>(tmpVal)) {    
      if (tmpVal->getType()->isIntegerType()) {
        condVal = IcmpInst::Create(
            c, IcmpInst::IcmpOp::NEQ, tmpVal,
            ConstantInt::get(c, tmpVal->getType(), 0),
            irBuilder->getBasicBlock());
      } else {
        condVal = FcmpInst::Create(c, FcmpInst::FcmpOp::NEQ, tmpVal,
                                  ConstantFloat::get(c, 0),
                                  irBuilder->getBasicBlock());
      }
    } else {
      condVal = tmpVal;
    }
    irBuilder->getBasicBlock()->addSuccessor(while_bb);
    irBuilder->getBasicBlock()->addSuccessor(next_bb);
    BranchInst::Create(c, condVal, while_bb, next_bb, irBuilder->getBasicBlock());    
  }
  irBuilder->setBasicBlock(while_bb);
  irBuilder->setLoopBlock(while_bb, next_bb);
  irBuilder->setBreakAndContinue(while_bb, next_bb);
  if (doStmt_) {
    irBuilder->setCond(cond_);
    doStmt_->generate(irBuilder);
    irBuilder->popCond(); 
  }
  irBuilder->popLoopBlock();
  irBuilder->popBreakAndContinueBlock();
  if (!irBuilder->getBasicBlock()->hasTerminator()) {
    irBuilder->getBasicBlock()->addSuccessor(while_bb);
    irBuilder->getBasicBlock()->addSuccessor(next_bb);
    irBuilder->setLoopBlock(while_bb, next_bb);
    irBuilder->setBreakAndContinue(while_bb, next_bb);
    cond_->generate(irBuilder);
    irBuilder->popBreakAndContinueBlock();
    irBuilder->popLoopBlock();
    auto tmpVal = irBuilder->getTmpVal();
    if (tmpVal) {    
      Value* condVal;
      if (!dynamic_cast<IcmpInst*>(tmpVal) && !dynamic_cast<FcmpInst*>(tmpVal)) {
        if (tmpVal->getType()->isPointerType()) {
          tmpVal = LoadInst::Create(c,tmpVal,irBuilder->getBasicBlock());
        }    
        if (tmpVal->getType()->isIntegerType()) {
          condVal = IcmpInst::Create(
              c, IcmpInst::IcmpOp::NEQ, tmpVal,
              ConstantInt::get(c, tmpVal->getType(), 0),
              irBuilder->getBasicBlock());
        } else {
          condVal = FcmpInst::Create(c, FcmpInst::FcmpOp::NEQ, tmpVal,
                                    ConstantFloat::get(c, 0),
                                    irBuilder->getBasicBlock());
        }        
      } else {
        condVal = tmpVal;
      }
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
  irBuilder->getBasicBlock()->addSuccessor(irBuilder->getBreakBlock());
  BranchInst::Create(irBuilder->getContext(),irBuilder->getBreakBlock(),irBuilder->getBasicBlock());
  // irBuilder->getBasicBlock()->addSuccessor(irBuilder->getNextBlock());
  // BranchInst::Create(irBuilder->getContext(),irBuilder->getNextBlock(),irBuilder->getBasicBlock());
}

void ContinueStatement::generate(IRBuilder *irBuilder) {
  Context& c = irBuilder->getContext();
  irBuilder->setLoopBlock(irBuilder->getContinueBlock(), irBuilder->getBreakBlock());
  // irBuilder->setLoopBlock(irBuilder->getWhileBlock(), irBuilder->getNextBlock());
  irBuilder->getCond()->generate(irBuilder);
  irBuilder->popLoopBlock();
  auto tmpVal = irBuilder->getTmpVal();
  if (tmpVal) {    
    Value* condVal;
    if (!dynamic_cast<IcmpInst*>(tmpVal) && !dynamic_cast<FcmpInst*>(tmpVal)) {
      if (tmpVal->getType()->isPointerType()) {
        tmpVal = LoadInst::Create(c,tmpVal,irBuilder->getBasicBlock());
      }    
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
    } else {
      condVal = tmpVal;
    }
    irBuilder->getBasicBlock()->addSuccessor(irBuilder->getContinueBlock());
    irBuilder->getBasicBlock()->addSuccessor(irBuilder->getBreakBlock());
    BranchInst::Create(c, condVal, irBuilder->getContinueBlock(), irBuilder->getBreakBlock(), irBuilder->getBasicBlock());    
    // irBuilder->getBasicBlock()->addSuccessor(irBuilder->getWhileBlock());
    // irBuilder->getBasicBlock()->addSuccessor(irBuilder->getNextBlock());
    // BranchInst::Create(c, condVal, irBuilder->getWhileBlock(), irBuilder->getNextBlock(), irBuilder->getBasicBlock());    
  }
}

void EvalStatement::generate(IRBuilder *irBuilder) {
  value_->generate(irBuilder);
}

void FuncCallExpression::generate(IRBuilder *irBuilder) {
  Context &context = irBuilder->getContext();
  auto func_name = identifier_->id_;
  if (func_name == "starttime" || func_name == "stoptime") {
    func_name = "_sysy_" + func_name;
  }
  auto func = dynamic_cast<Function*>(irBuilder->getModule()->symbolTable_[func_name]);
  auto funcType = static_cast<FunctionType*>(func->getFunctionType());
  vector<Value*>funcArgs;
  for(int u = 0, len = funcType->getArgumentsNum(); u < len; u++) {
    actualArgs_->list_[u]->generate(irBuilder);
    auto val = irBuilder->getTmpVal();
    if (val->getType()->isPointerType()) {
      if (!dynamic_cast<GetElementPtrInst*>(val)){
        val = LoadInst::Create(context, val, irBuilder->getBasicBlock());
      } else {
        if (!funcType->getArgumentType(u)->isPointerType()) {          
          val = LoadInst::Create(context, val, irBuilder->getBasicBlock());
        } else if (val->getType() != funcType->getArgumentType(u)){
          val = GetElementPtrInst::Create(context, val, {
            ConstantInt::get(context, context.Int32Type, 0),
            ConstantInt::get(context, context.Int32Type, 0)
          }, irBuilder->getBasicBlock());
        }
      }
    } 
    if (val->getType() != funcType->getArgumentType(u)) {
      if (funcType->getArgumentType(u)->isIntegerType()) {
        val = FpToSiInst::Create(context, funcType->getArgumentType(u), val, irBuilder->getBasicBlock());
      } else {
        val = SiToFpInst::Create(context, funcType->getArgumentType(u), val, irBuilder->getBasicBlock());      
      }
    }
    if(dynamic_cast<ConstantInt*>(val) && funcType->getArgumentType(u) == context.FloatType)
      funcArgs.emplace_back(ConstantFloat::get(context, static_cast<float>(dynamic_cast<ConstantInt*>(val)->getValue())));
    else if(dynamic_cast<ConstantFloat*>(val) && funcType->getArgumentType(u) != context.FloatType) 
      funcArgs.emplace_back(ConstantInt::get(context, 
                                             funcType->getArgumentType(u),
                                             static_cast<int>(dynamic_cast<ConstantFloat*>(val)->getValue())));
    else funcArgs.emplace_back(val);
  }
  auto tmp = CallInst::Create(context, dynamic_cast<Function*>(irBuilder->getModule()->symbolTable_[func_name]),
                   funcArgs, 
                   irBuilder->getBasicBlock());
  irBuilder->setTmpVal(tmp);
} 
