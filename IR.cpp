#include "IR.h"

Context::Context()
    : VoidType(new Type(Type::TypeId::VoidTypeId)),
      FloatType(new Type(Type::TypeId::FloatTypeId)),
      LabelType(new Type(Type::TypeId::LabelTypeId)),
      Int1Type(new IntegerType(1)), Int32Type(new IntegerType(32)) {}

Context::~Context() {
  delete VoidType;
  delete LabelType;
  delete FloatType;
  delete Int1Type;
  delete Int32Type;
  for (auto &ptr : PointerTypes) {
    delete ptr.second;
  }
  for (auto &arr : ArrayTypes) {
    delete arr.second;
  }
}

void Context::addModule(Module *module) { ownerModule = module; }

PointerType *Context::getPtrType(Type *ptrElementType) {
  if (PointerTypes.find(ptrElementType) == PointerTypes.end()) {
    PointerTypes[ptrElementType] = new PointerType(ptrElementType);
  }
  return PointerTypes[ptrElementType];
}

ArrayType *Context::getArrayType(Type *elementType, std::size_t elementNum) {
  if (ArrayTypes.find({elementType, elementNum}) == ArrayTypes.end()) {
    ArrayTypes[{elementType, elementNum}] =
        new ArrayType(elementType, elementNum);
  }
  return ArrayTypes[{elementType, elementNum}];
}

Type::Type(TypeId typdId) : typeId_(typdId) {}

bool Type::operator==(const Type &type) { return typeId_ == type.typeId_; }

Type *Type::getVoidType(Context &context) { return context.VoidType; }

Type *Type::getLabelType(Context &context) { return context.LabelType; }

IntegerType *Type::getInt1Type(Context &context) { return context.Int1Type; }

IntegerType *Type::getInt32Type(Context &context) { return context.Int32Type; }

Type *Type::getFloatType(Context &context) { return context.FloatType; }

PointerType *Type::getPtrType(Context &context, Type *ptrElementType) {
  return PointerType::get(context, ptrElementType);
}

ArrayType *Type::getArrayType(Context &context, Type *elementType,
                              std::size_t elementNum) {
  return ArrayType::get(context, elementType, elementNum);
}

std::string Type::getTypeName() {
  std::string typeName;
  switch (typeId_) {
  case TypeId::VoidTypeId:
    typeName = "void";
    break;
  case TypeId::LabelTypeId:
    typeName = "label";
    break;
  case TypeId::IntegerTypeId:
    typeName +=
        "i" + std::to_string(static_cast<IntegerType *>(this)->getBitsNum());
    break;
  case TypeId::FunctionTypeId:
    typeName +=
        static_cast<FunctionType *>(this)->getReturnType()->getTypeName();
    typeName += " (";
    for (int i = 0; i < static_cast<FunctionType *>(this)->getArgumentsNum();
         i++) {
      if (i)
        typeName += ", ";
      typeName +=
          static_cast<FunctionType *>(this)->getArgumentType(i)->getTypeName();
    }
    typeName += ")";
    break;
  case TypeId::PointerTypeId:
    typeName += this->getPtrElementType()->getTypeName();
    typeName += "*";
    break;
  case TypeId::ArrayTypeId:
    typeName += "[";
    if (static_cast<ArrayType *>(this)->getElementNum() != -1){
      typeName += std::to_string(static_cast<ArrayType *>(this)->getElementNum());
    } else {
      typeName += "■";
    }
    typeName += " x ";
    typeName += static_cast<ArrayType *>(this)->getElementType()->getTypeName();
    typeName += "]";
    break;
  case TypeId::FloatTypeId:
    typeName += "float";
    break;
  default:
    break;
  }
  return typeName;
}

Type *Type::getPtrElementType() {
  if (this->isPointerType())
    return static_cast<PointerType *>(this)->getPtrElementType();
  else
    return nullptr;
}

IntegerType::IntegerType(std::size_t bitsNum)
    : Type(TypeId::IntegerTypeId), bitsNum_(bitsNum) {}

std::size_t IntegerType::getBitsNum() { return bitsNum_; }

IntegerType *IntegerType::get(std::size_t bitsNum) {
  return new IntegerType(bitsNum);
}

PointerType::PointerType(Type *ptrElementType)
    : Type(TypeId::PointerTypeId), ptrElementType_(ptrElementType) {}

PointerType *PointerType::get(Context &context, Type *ptrElementType) {
  return context.getPtrType(ptrElementType);
}

Type *PointerType::getPtrElementType() { return ptrElementType_; }

ArrayType::ArrayType(Type *elementType, std::size_t elementNum)
    : Type(TypeId::ArrayTypeId), elementType_(elementType),
      elementNum_(elementNum) {}

ArrayType *ArrayType::get(Context &context, Type *elementType,
                          std::size_t elementNum) {
  return context.getArrayType(elementType, elementNum);
}

ArrayType *ArrayType::get(Context &context, Type *elementType,
                          std::vector<int> dimension) {
  assert(dimension.size() != 0);
  ArrayType *arr_type;
  int i = dimension.size() - 1;
  arr_type = ArrayType::get(context, elementType, dimension[i--]);
  for (; i >= 0; i--) {
    arr_type = ArrayType::get(context, arr_type, dimension[i]);
  }
  return arr_type;
}

Type *ArrayType::getElementType() { return elementType_; }

std::size_t ArrayType::getElementNum() { return elementNum_; }

std::size_t ArrayType::getAllElementNum(){
  int size = getElementNum();
  if (elementType_->isArrayType()) {
    size *= static_cast<ArrayType*>(elementType_)->getAllElementNum();
  }
  return size;
}

FunctionType::FunctionType(Type *resultType)
    : Type(TypeId::FunctionTypeId), resultType_(resultType) {}

FunctionType::FunctionType(Type *resultType, std::vector<Type *> argumentsType)
    : Type(TypeId::FunctionTypeId), resultType_(resultType),
      argumentsType_(argumentsType) {}

FunctionType *FunctionType::get(Type *resultType) {
  return new FunctionType(resultType);
}

FunctionType *FunctionType::get(Type *resultType,
                                std::vector<Type *> paramsType) {
  return new FunctionType(resultType, paramsType);
}

std::size_t FunctionType::getArgumentsNum() { return argumentsType_.size(); }

Type *FunctionType::getReturnType() { return resultType_; }

Type *FunctionType::getArgumentType(std::size_t idx) {
  return argumentsType_[idx];
}

Value::Value(Type *type, const std::string &name) : type_(type), name_(name) {}

Value::Value(Context &c, Type *type, const std::string &name) : type_(type), name_(name), no_(c.counter++) {}

bool Value::setName(const std::string &name) {
  if (name_ == "") {
    name_ = name;
    return true;
  }
  return false;
}

// why copy
std::string Value::getName() { return name_; }

std::string Value::getLLVM_Name() { 
  return name_ + std::to_string(no_); }

Type *Value::getType() { return type_; }

size_t Value::getNO() { return no_; }

void Value::addUse(const Use &u) { useList_.emplace_front(u); }

void Value::removeUse(Value *val) { 
  auto is_val = [val] (Use &use) { return use.getUser() == val; };
  useList_.remove_if(is_val);
}

void Value::replaceAllUseWith(Value *new_val) {
  for (auto use : useList_) {
    auto val = dynamic_cast<User *>(use.getUser());
    assert(val && "new_val is not a user");
    val->setOperand(new_val, use.getArgNo());
  }
}


Use::Use(User *user,Value* value, unsigned argNo) : user_(user),value_(value), argNo_(argNo) {}

Value *Use::getValue() { return value_; }

User *Use::getUser() { return user_; }

User::User(Type *type, const std::string &name, std::size_t operandNum)
    : Value(type, name), operandNum_(operandNum), operands_(operandNum) {}

User::User(Context &c, Type *type, const std::string &name, std::size_t operandNum)
    : Value(c, type, name), operandNum_(operandNum), operands_(operandNum) {}

std::size_t User::getOperandNum() { return operandNum_; }

Value *User::getOperand(std::size_t idx) { return operands_[idx]; }

Type *User::getOperandType(std::size_t idx) {
  return operands_[idx]->getType();
}

std::string User::getOperandTypeName(std::size_t idx) {
  return operands_[idx]->getType()->getTypeName();
}

void User::setOperand(Value *value, std::size_t idx) {
  assert(idx < operandNum_ && "setOperand out of index");
  operands_[idx] = value;
  value->addUse(Use(this, value, idx));
}

void User::addOperand(Value *value) {
  operands_.emplace_back(value);  
  Use u(this, value, operandNum_);
  value->addUse(u);
  operandNum_++;
}

std::string ConstantInt::print() {
  std::string const_ir;
  Type *ty = getType();
  if (ty->isIntegerType() &&
      static_cast<IntegerType *>(ty)->getBitsNum() == 1) {
    // int1
    const_ir += (getValue() == 0) ? "false" : "true";
  } else {
    // int32
    const_ir += std::to_string(getValue());
  }
  return const_ir;
}

ConstantFloat *ConstantFloat::get(Context &context, float value) {
  return new ConstantFloat(context, Type::getFloatType(context), value);
}

std::string ConstantFloat::print() {
  std::string fp_ir;
  char dstr[20];
  snprintf(dstr, 20, "%.8lf", value_);
  fp_ir.assign(dstr);
  return fp_ir;
}

ConstantZero *ConstantZero::get(Context &c, Type *type) { return new ConstantZero(c, type); }

std::string ConstantZero::print() { return "zeroinitializer"; }

ConstantArray::ConstantArray(Context &c, ArrayType *type,
                             const std::vector<Value *> &value,
                             const std::vector<int> &dimension)
    : Constant(c, type, "", value.size()), value_(value), dimension_(dimension) {
  for (int i = 0; i < value.size(); i++) {
    setOperand(value_[i], i);
  }
}

ConstantArray *ConstantArray::get(Context &c, ArrayType *type,
                                  const std::vector<Value *> &value, const std::vector<int> &dimension) {
  return new ConstantArray(c, type, value, dimension);
}

Value *ConstantArray::getElementValue(int idx) { 
  if (idx >= value_.size()) {
    throw Exception("out of array bound");
  }
  return value_[idx]; 
}

std::string ConstantArray::print() {
  std::string const_ir;
  if (!dynamic_cast<ConstantZero*>(getElementValue(value_.size() - 1))) {
    const_ir += "[";
    const_ir += std::to_string(value_.size());
    const_ir += " x ";
    const_ir += getElementValue(0)->getType()->getTypeName();
    const_ir += "] ";    
    const_ir += "[ ";
    for (int i = 0; i < value_.size(); i++) {
      const_ir += getElementValue(i)->getType()->getTypeName();
      const_ir += " ";
      const_ir += getElementValue(i)->print();
      if (i < value_.size() - 1) {
        const_ir += ", ";
      }
    }
    const_ir += " ]";     
  } else {
    if (dynamic_cast<ConstantZero*>(getElementValue(0))) {    
      const_ir += getType()->getTypeName();
      const_ir += " ";
      const_ir += getElementValue(0)->print();
    }else {      
      const_ir += "<{ ";
      for (int i = 0; i < value_.size(); i++) {
        if (dynamic_cast<ConstantZero*>(getElementValue(i))) {
          const_ir += "[";
          const_ir += std::to_string(value_.size() - i);
          const_ir += " x ";
          const_ir += getElementValue(i)->getType()->getTypeName();
          const_ir += "]";
          break;
        }
        const_ir += getElementValue(i)->getType()->getTypeName();
        if (i < value_.size() - 1) {
          const_ir += ", ";
        }
      }  
      const_ir += " }> ";
      const_ir += "<{ ";
      for (int i = 0; i < value_.size(); i++) {
        if (dynamic_cast<ConstantZero*>(getElementValue(i))) {
          const_ir += "[";
          const_ir += std::to_string(value_.size() - i);
          const_ir += " x ";
          const_ir += getElementValue(i)->getType()->getTypeName();
          const_ir += "] ";
          const_ir += getElementValue(i)->print();
          break;
        }
        const_ir += getElementValue(i)->getType()->getTypeName();
        const_ir += " ";
        const_ir += getElementValue(i)->print();
        if (i < value_.size() - 1) {
          const_ir += ", ";
        }
      }
      const_ir += " }>"; 
    }
  }
  return const_ir;
}

Argument::Argument(Context &c, Type *type, const std::string &name, Function *func,
                   std::size_t argumentNo)
    : Value(c, type, name), parent_(func), argumentNo_(argumentNo) {}

std::string Argument::print() {
   return getLLVM_Name(); 
}

Module::Module(Context &context, const std::string &moduleName)
    : context_(context), moduleName_(moduleName) {
  context_.addModule(this);
}

void Module::addFuntion(Function *func) { functionList_.emplace_back(func); }

void Module::addGlobalVariable(GlobalVariable *globalVariable) {
  globalVariableList_.emplace(globalVariable);
}

std::string Module::print() {
  std::string module_ir;
  for (auto global_val : globalVariableList_) {
    module_ir += global_val->print();
    module_ir += "\n";
  }
  for (auto &func : functionList_) {
    module_ir += func->print();
    module_ir += "\n";
  }
  return module_ir;
}

Function::Function(Context &c, FunctionType *funcType, const std::string args_name[], const std::string &funcName,
                   Module *parent, bool is_decl, bool inLib)
    : Value(funcType, funcName), parent_(parent) {
  assert(parent != nullptr);
  name_ = funcName;

  parent_->addFuntion(this);
  parent_->symbolTable_[funcName] = this;
  for (int i = 0; i < getArgumentsNum(); i++) {
    arguments_.emplace_back(
        new Argument(c, funcType->getArgumentType(i), args_name[i], this, i));
  }
  is_declaration = is_decl;
  is_libFn = inLib;
}

Function *Function::Create(Context &c, FunctionType *funcType, const std::string args_name[], const std::string &funcName,
                           Module *parent, bool is_decl, bool inLib) {
  assert(parent != nullptr);
  return new Function(c ,funcType, args_name, funcName, parent, is_decl, inLib);
}

Module *Function::getModule() { return parent_; }

Type *Function::getReturnType() { return getFunctionType()->getReturnType(); }

std::size_t Function::getArgumentsNum() {
  return getFunctionType()->getArgumentsNum();
}

FunctionType *Function::getFunctionType() {
  return static_cast<FunctionType *>(getType());
}

void Function::addBasicBlock(BasicBlock *bb) { basicBlocks_.emplace_back(bb); }

std::list<BasicBlock *>& Function::getBasicBlocks() {return basicBlocks_;}

void Function::remove(BasicBlock* bb){
  basicBlocks_.remove(bb);
}


Argument *Function::getArgument(size_t idx) { 
  assert(idx < getArgumentsNum() && "argument idx is out of range");
  return arguments_[idx];
}

std::string Function::print() {
  std::string func_ir;
  // set_instr_name();
  if (this->is_declaration) {
     func_ir += "declare ";
   } else {
  func_ir += "define ";
  }

  func_ir += getReturnType()->getTypeName();
  func_ir += " ";
  func_ir += print_as_op(this);
  func_ir += "(";

  int args_num = getArgumentsNum();
  for (int i = 0; i < args_num; i++){
    auto arg = arguments_[i];
    func_ir += arg->getType()->getTypeName();
    func_ir += " ";
    func_ir += print_as_op(arg);

    if (args_num-1 > i){
      func_ir += ", ";
    }
  }

  func_ir += ")";
  // // print arg
  //     if (i)
  //       func_ir += ", ";
  //     func_ir += static_cast<FunctionType *>(this->get_type())
  //                    ->get_param_type(i)
  //                    ->print();
  //   }
  // } else {
  //   for (auto arg = this->arg_begin(); arg != arg_end(); arg++) {
  //     if (arg != this->arg_begin()) {
  //       func_ir += ", ";
  //     }
  //     func_ir += static_cast<Argument *>(*arg)->print();
  //   }
  // }
  // func_ir += ")";

  // print bb
  // if (this->is_declaration()) {
  //   func_ir += "\n";
  // } else {
  if (is_declaration) { return func_ir; }
  func_ir += " {";
  func_ir += "\n";
  for (auto bb : basicBlocks_) {
    func_ir += bb->print();
  }
  func_ir += "}";
  // }
  // std::cout << func_ir << std::endl;
  return func_ir;
}

GlobalVariable::GlobalVariable(Context &c, Type *type, const std::string &globalVarName,
                               bool isConst, Constant *initializer,
                               Module *insertedModule)
    : User(c, type, globalVarName, 1), initValue_(initializer),isConst_(isConst) {
  setOperand(initializer, 0);
  insertedModule->symbolTable_[globalVarName] = this;
  insertedModule->addGlobalVariable(this);
}

GlobalVariable *GlobalVariable::Create(Context &c, Type *type,
                                       const std::string &globalVarName,
                                       bool isConst, Constant *initializer,
                                       Module *insertedModule) {
  return new GlobalVariable(c, Type::getPtrType(c, type), globalVarName, isConst, initializer,
                            insertedModule);
}
std::string GlobalVariable::print() {
  std::string global_val_ir;
  global_val_ir += print_as_op(this);
  global_val_ir += " = ";
  global_val_ir += (isConst_ ? "constant " : "global ");
  if (!dynamic_cast<ConstantArray*>(initValue_)) {
    global_val_ir += getType()->getPtrElementType()->getTypeName();
    global_val_ir += " ";
  }
  global_val_ir += initValue_->print();
  return global_val_ir;
}

BasicBlock::BasicBlock(Context &context, const std::string &name,
                       Function *parent)
    : Value(context, Type::getLabelType(context), name), parent_(parent) {
  assert(parent_ != nullptr);
  parent_->addBasicBlock(this);
}

BasicBlock *BasicBlock::Create(Context &context, const std::string &name,
                               Function *parent) {
  assert(parent != nullptr);
  return new BasicBlock(context, name, parent);
}

bool BasicBlock::hasTerminator(){
  if (instructionList_.empty()|| !instructionList_.back()->isTerminator()) {
    return false;
  }
  return true;
}

void BasicBlock::eraseFromParent(){
  parent_->remove(this);
}

void BasicBlock::deleteInst(Instruction *inst) {
  instructionList_.remove(inst);
  inst->removeUseOfOps();
}


Module *BasicBlock::getModule() { return parent_->getModule(); }

void BasicBlock::addInstruction(Instruction *instruction) {
  instructionList_.emplace_back(instruction);
}

void BasicBlock::addPredecessor(BasicBlock* pre) {
  if (std::find(predecessorBlocks_.begin(), predecessorBlocks_.end(), pre) == predecessorBlocks_.end()) {  
    predecessorBlocks_.emplace_back(pre);
  }
}

void BasicBlock::addSuccessor(BasicBlock* suc) {
  if (std::find(successorBlocks_.begin(), successorBlocks_.end(), suc) == successorBlocks_.end()) {  
    successorBlocks_.emplace_back(suc);
  }
  suc->addPredecessor(this);
}

void BasicBlock::addDominator(BasicBlock *dom) {
  dominators_.emplace(dom);
}

void BasicBlock::setDominators(std::set<BasicBlock *> &doms) {
  dominators_ = doms;
}


std::set<BasicBlock *>& BasicBlock::getDominators() {
  return dominators_;
}

std::list<BasicBlock *>& BasicBlock::getSuccessor() {
  return successorBlocks_;
}

std::list<BasicBlock *>& BasicBlock::getPredecessors() {
  return predecessorBlocks_;
}

std::string BasicBlock::print() {
  std::string bb_ir;
  bb_ir += getLLVM_Name();
  bb_ir += ":";
  bb_ir += "\n";
  for (auto instr : instructionList_) {
    bb_ir += "  ";
    bb_ir += instr->print();
    bb_ir += "\n";
  }
  return bb_ir;
}

Instruction::Instruction(Type *type, InstId instId, std::size_t operandNum,
                         BasicBlock *parent)
    : User(type, "", operandNum), instId_(instId), parent_(parent) {}

Instruction::Instruction(Type *type, InstId instId, std::size_t operandNum,
                         BasicBlock *parent, std::string name)
    : User(type, name, operandNum), instId_(instId), parent_(parent) {}

Instruction::Instruction(Context &c, Type *type, InstId instId, std::size_t operandNum,
                         BasicBlock *parent, std::string name)
    : User(c, type, name, operandNum), instId_(instId), parent_(parent) {}

Module *Instruction::getModule() { return parent_->getModule(); }

bool Instruction::isVoid() {
  return ((instId_ == InstId::Ret) || (instId_ == InstId::Br) ||
          (instId_ == InstId::Store) ||
          (instId_ == InstId::Call && getType()->isVoidType()));
}

bool Instruction::isPhi() { return instId_ == InstId::Phi; }
bool Instruction::isStore() { return instId_ == InstId::Store; }
bool Instruction::isAlloca() { return instId_ == InstId::Alloca; }
bool Instruction::isRet() { return instId_ == InstId::Ret; }
bool Instruction::isLoad() { return instId_ == InstId::Load; }
bool Instruction::isBr() { return instId_ == InstId::Br; }

bool Instruction::isAdd() { return instId_ == InstId::Add; }
bool Instruction::isSub() { return instId_ == InstId::Sub; }
bool Instruction::isMul() { return instId_ == InstId::Mul; }
bool Instruction::isDiv() { return instId_ == InstId::Sdiv; }
bool Instruction::isMod() { return instId_ == InstId::Mod; }

bool Instruction::isAnd() { return instId_ == InstId::And; }
bool Instruction::isOr() { return instId_ == InstId::Or; }

bool Instruction::isFadd() { return instId_ == InstId::Fadd; }
bool Instruction::isFsub() { return instId_ == InstId::Fsub; }
bool Instruction::isFmul() { return instId_ == InstId::Fmul; }
bool Instruction::isFdiv() { return instId_ == InstId::Fdiv; }
bool Instruction::isFp2si() { return instId_ == InstId::Fptosi; }
bool Instruction::isSi2fp() { return instId_ == InstId::Sitofp; }

bool Instruction::isIcmp() { return instId_ == InstId::Icmp; }
bool Instruction::isFcmp() { return instId_ == InstId::Fcmp; }

bool Instruction::isCall() { return instId_ == InstId::Call; }
bool Instruction::isGep() { return instId_ == InstId::Getelementptr; }
bool Instruction::isZext() { return instId_ == InstId::Zext; }
bool Instruction::isNot() { return instId_ == InstId::Not; }
bool Instruction::isNegative(){ return instId_ == InstId::Negative; }


bool Instruction::isBinary() {
  return (isAdd() || isSub() || isMul() || isDiv() || isMod() || isFadd() || isFsub() ||
          isFmul() || isFdiv() || isAnd() || isOr() || isIcmp() || isFcmp()) &&
         (getOperandNum() == 2);
}

bool Instruction::isTerminator() { return isBr() || isRet(); }

std::string Instruction::getInstructionOpName() {
  std::string instName;
  switch (instId_) {
  case InstId::Ret:
    instName = "ret";
    break;
  case InstId::Br:
    instName = "br";
    break;
  case InstId::Add:
    instName = "add";
    break;
  case InstId::Sub:
    instName = "sub";
    break;
  case InstId::Mul:
    instName = "mul";
    break;
  case InstId::Sdiv:
    instName = "sdiv";
    break;
  case InstId::Mod:
    instName = "srem";
    break;
  case InstId::Fadd:
    instName = "fadd";
    break;
  case InstId::Fsub:
    instName = "fsub";
    break;
  case InstId::Fmul:
    instName = "fmul";
    break;
  case InstId::Fdiv:
    instName = "fdiv";
    break;
  case InstId::And:
    instName = "and";
    break;
  case InstId::Or:
    instName = "or";
    break;
  case InstId::Alloca:
    instName = "alloca";
    break;
  case InstId::Load:
    instName = "load";
    break;
  case InstId::Store:
    instName = "store";
    break;
  case InstId::Icmp:
    instName = "cmp";
    break;
  case InstId::Fcmp:
    instName = "fcmp";
    break;
  case InstId::Phi:
    instName = "phi";
    break;
  case InstId::Call:
    instName = "call";
    break;
  case InstId::Getelementptr:
    instName = "getelementptr";
    break;
  case InstId::Zext:
    instName = "zext";
    break;
  case InstId::Fptosi:
    instName = "fptosi";
    break;
  case InstId::Sitofp:
    instName = "sitofp";
    break;
  case InstId::Negative:
    instName = "negative";
    break;
  case InstId::Not:
    instName = "not";
    break;
  default:
    break;
  }
  return instName;
}

AllocaInst::AllocaInst(Context &context, Type *allocaType,
                       BasicBlock *insertedBlock, std::string name)
    : Instruction(context, PointerType::get(context, allocaType), InstId::Alloca, 0,
                  insertedBlock, name),
      allocaType_(allocaType) {
  insertedBlock->addInstruction(this);
}

AllocaInst *AllocaInst::Create(Context &context, Type *allocaType,
                               BasicBlock *insertedBlock, std::string name) {
  return new AllocaInst(context, allocaType, insertedBlock, name);
}

Type *AllocaInst::getAllocaType() { return allocaType_; }

std::string AllocaInst::print() {
  std::string IR;
  char IRtemp[100];
  // <result> = alloca <type>
  std::string fmt("%%%s = alloca %s");
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                allocaType_->getTypeName().c_str());
  IR.assign(IRtemp);
  return IR;
}

BinaryInst::BinaryInst(Context &c, Type *type, InstId instId, Value *leftValue,
                       Value *rightValue, BasicBlock *insertedBlock, std::string name)
    : Instruction(c, type, instId, 2, insertedBlock, name) {
  setOperand(leftValue, 0);
  setOperand(rightValue, 1);
  insertedBlock->addInstruction(this);
}

BinaryInst *BinaryInst::CreateAdd(Context &context, Value *leftValue,
                                  Value *rightValue,
                                  BasicBlock *insertedBlock, std::string name) {
  return new BinaryInst(context, leftValue->getType(), InstId::Add, leftValue,
                        rightValue, insertedBlock, name);
}

BinaryInst *BinaryInst::CreateSub(Context &context, Value *leftValue,
                                  Value *rightValue,
                                  BasicBlock *insertedBlock, std::string name) {
  return new BinaryInst(context, leftValue->getType(), InstId::Sub, leftValue,
                        rightValue, insertedBlock, name);
}

BinaryInst *BinaryInst::CreateMul(Context &context, Value *leftValue,
                                  Value *rightValue,
                                  BasicBlock *insertedBlock, std::string name) {
  return new BinaryInst(context, leftValue->getType(), InstId::Mul, leftValue,
                        rightValue, insertedBlock, name);
}

BinaryInst *BinaryInst::CreateSdiv(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock, std::string name) {
  return new BinaryInst(context, leftValue->getType(), InstId::Sdiv, leftValue,
                        rightValue, insertedBlock, name);
}

BinaryInst *BinaryInst::CreateMod(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock, std::string name) {
  return new BinaryInst(context, leftValue->getType(), InstId::Mod, leftValue,
                        rightValue, insertedBlock, name);
}

BinaryInst *BinaryInst::CreateFadd(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock, std::string name) {
  return new BinaryInst(context, Type::getFloatType(context), InstId::Fadd, leftValue,
                        rightValue, insertedBlock, name);
}

BinaryInst *BinaryInst::CreateFsub(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock, std::string name) {
  return new BinaryInst(context, Type::getFloatType(context), InstId::Fsub, leftValue,
                        rightValue, insertedBlock, name);
}

BinaryInst *BinaryInst::CreateFmul(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock, std::string name) {
  return new BinaryInst(context, Type::getFloatType(context), InstId::Fmul, leftValue,
                        rightValue, insertedBlock, name);
}

BinaryInst *BinaryInst::CreateFdiv(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock, std::string name) {
  return new BinaryInst(context, Type::getFloatType(context), InstId::Fdiv, leftValue,
                        rightValue, insertedBlock, name);
}

BinaryInst *BinaryInst::CreateAnd(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock, std::string name) {
  return new BinaryInst(context, leftValue->getType(), InstId::And, leftValue,
                        rightValue, insertedBlock, name);
}

BinaryInst *BinaryInst::CreateOr(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock, std::string name) {
  return new BinaryInst(context, leftValue->getType(), InstId::Or, leftValue,
                        rightValue, insertedBlock, name);
}

std::string BinaryInst::print() {
  std::string IR;
  char IRtemp[100];
  if (getOperandType(0) == getOperandType(1)) {
    // <result> = add <type> <op1>, <op2>
    std::string fmt;
    if (isAdd() || isSub()) {
      fmt = "%%%s = %s nsw %s %s, %s";
    } else {
      fmt = "%%%s = %s %s %s, %s";    
    }
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                  getInstructionOpName().c_str(), getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str(),
                  print_as_op(getOperand(1)).c_str());
  } else {
    // <result> = add <type> <op1>, <type> <op2>
    std::string fmt;
    if (isAdd() || isSub()) {
      fmt = "%%%s = %s nsw %s %s, %s %s";
    } else {
      fmt = "%%%s = %s %s %s, %s %s";
    }
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                  getInstructionOpName().c_str(), getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str(),
                  getOperandTypeName(1).c_str(),
                  print_as_op(getOperand(1)).c_str());
  }
  IR.assign(IRtemp);
  return IR;
}

BranchInst::BranchInst(Context &context, BasicBlock *ifTrueBlock,
                       BasicBlock *insertedBlock)
    : Instruction(Type::getVoidType(context), InstId::Br, 1, insertedBlock) {
  setOperand(ifTrueBlock, 0);
  insertedBlock->addInstruction(this);
}

BranchInst::BranchInst(Context &context, Value *cond, BasicBlock *ifTrueBlock,
                       BasicBlock *ifFalseBlock, BasicBlock *insertedBlock)
    : Instruction(Type::getVoidType(context), InstId::Br, 3, insertedBlock) {
  setOperand(cond, 0);
  setOperand(ifTrueBlock, 1);
  setOperand(ifFalseBlock, 2);
  insertedBlock->addInstruction(this);
}

BranchInst *BranchInst::Create(Context &context, BasicBlock *ifTrueBlock,
                               BasicBlock *insertedBlock) {
  return new BranchInst(context, ifTrueBlock, insertedBlock);
}

BranchInst *BranchInst::Create(Context &context, Value *cond,
                               BasicBlock *ifTrueBlock,
                               BasicBlock *ifFalseBlock,
                               BasicBlock *insertedBlock) {
  return new BranchInst(context, cond, ifTrueBlock, ifFalseBlock,
                        insertedBlock);
}

bool BranchInst::isCondBr() { return getOperandNum() == 3; }

std::string BranchInst::print() {
  std::string IR;
  char IRtemp[100];
  if (isCondBr()) {
    // br i1 <cond>, label <iftrue>, label <iffalse>
    std::string fmt("br i1 %s, label %s, label %s");
    std::snprintf(
        IRtemp, sizeof IRtemp, fmt.c_str(), print_as_op(getOperand(0)).c_str(),
        print_as_op(getOperand(1)).c_str(), print_as_op(getOperand(2)).c_str());
  } else {
    // br label <dest>
    std::string fmt("br label %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(),
                  print_as_op(getOperand(0)).c_str());
  }
  IR.assign(IRtemp);
  return IR;
}

CallInst::CallInst(Context& c, Function *func, std::vector<Value *> funcArgs,
                   BasicBlock *insertedBlock, std::string name)
    : Instruction(c, func->getReturnType(), InstId::Call, funcArgs.size() + 1,
                  insertedBlock, name) {
  assert(func->getArgumentsNum() == funcArgs.size());
  setOperand(func, 0);
  for (int i = 0; i < funcArgs.size(); i++) {
    setOperand(funcArgs[i], i + 1);
  }
  insertedBlock->addInstruction(this);
}

CallInst *CallInst::Create(Context& c, Function *func, std::vector<Value *> funcArgs,
                           BasicBlock *insertedBlock, std::string name) {
  return new CallInst(c, func, funcArgs, insertedBlock, name);
}

FunctionType *CallInst::getFunctionType() {
  return static_cast<FunctionType *>(getOperand(0)->getType());
}

std::string CallInst::print() {
  std::string IR;
  char IRtemp[100];
  if (!isVoid()) {
    // <result> = call <return ty> <func name>(<function args>)
    std::string fmt("%%%s = call %s %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                  getType()->getTypeName().c_str(),
                  print_as_op(getOperand(0)).c_str());
  } else {
    // call <return ty> <func name>(<function args>)
    std::string fmt("call %s %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(),
                  getType()->getTypeName().c_str(),
                  print_as_op(getOperand(0)).c_str());
  }
  IR.assign(IRtemp);
  IR += "(";
  for (int i = 1; i < getOperandNum(); i++) {
    if (i > 1)
      IR += ", ";
    IR += this->getOperand(i)->getType()->getTypeName() + " " +
          print_as_op(getOperand(i));
  }
  IR += ")";
  return IR;
}

FcmpInst::FcmpInst(Context &c, Type *type, FcmpOp fcmpOp, Value *leftValue,
                   Value *rightValue, BasicBlock *insertedBlock, std::string name)
    : Instruction(c, type, InstId::Fcmp, 2, insertedBlock, name), fcmpOp_(fcmpOp) {
  setOperand(leftValue, 0);
  setOperand(rightValue, 1);
  insertedBlock->addInstruction(this);
}

FcmpInst *FcmpInst::Create(Context &context, FcmpOp fcmpOp, Value *leftValue,
                           Value *rightValue, BasicBlock *insertedBlock, std::string name) {
  return new FcmpInst(context, Type::getInt1Type(context), fcmpOp, leftValue, rightValue,
                      insertedBlock, name);
}

FcmpInst::FcmpOp FcmpInst::getFcmpOp() { return fcmpOp_; }

std::string FcmpInst::getFcmpOpName() {
  std::string icmpOpName;
  switch (fcmpOp_) {
  case FcmpOp::EQ:
    icmpOpName = "eq";
    break;
  case FcmpOp::NEQ:
    icmpOpName = "ne";
    break;
  case FcmpOp::GT:
    icmpOpName = "ugt";
    break;
  case FcmpOp::GTE:
    icmpOpName = "uge";
    break;
  case FcmpOp::LT:
    icmpOpName = "ult";
    break;
  case FcmpOp::LTE:
    icmpOpName = "ule";
    break;
  default:
    icmpOpName = "fcmpOp error";
    break;
  }
  return icmpOpName;
}

std::string FcmpInst::print() {
  std::string IR;
  char IRtemp[100];
  if (getOperandType(0) == getOperandType(1)) {
    std::string fmt("%%%s = fcmp %s %s %s, %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                  getFcmpOpName().c_str(), getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str(),
                  print_as_op(getOperand(1)).c_str());
  } else {
    std::string fmt("%%%s = fcmp %s %s %s, %s %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                  getFcmpOpName().c_str(), getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str(),
                  getOperandTypeName(1).c_str(),
                  print_as_op(getOperand(1)).c_str());
  }
  IR.assign(IRtemp);
  return IR;
}

FpToSiInst::FpToSiInst(Context &c, Type *destType, Value *value, BasicBlock *insertedBlock, std::string name)
    : Instruction(c, destType, InstId::Fptosi, 1, insertedBlock, name),
      destType_(destType) {
  setOperand(value, 0);
  insertedBlock->addInstruction(this);
}

FpToSiInst *FpToSiInst::Create(Context &c, Type *destType, Value *value,
                               BasicBlock *insertedBlock, std::string name) {
  return new FpToSiInst(c, destType, value, insertedBlock, name);
}

Type *FpToSiInst::getDestType() { return destType_; }

std::string FpToSiInst::print() {
  std::string IR;
  char IRtemp[100];
  // <result> = fptosi <type> <value> to <type2>
  std::string fmt("%%%s = fptosi %s %s to %s");
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                getOperandType(0)->getTypeName().c_str(),
                print_as_op(getOperand(0)).c_str(),
                destType_->getTypeName().c_str());
  IR.assign(IRtemp);
  return IR;
}

GetElementPtrInst::GetElementPtrInst(Context &context, Value *ptr,
                                     std::vector<Value *> idxList,
                                     BasicBlock *insertedBlock,
                                     std::string name)
    : Instruction(
          context, PointerType::get(context, computeElementType(ptr, idxList)),
          InstId::Getelementptr, idxList.size() + 1, insertedBlock, name) {
  setOperand(ptr, 0);
  for (int i = 0; i < idxList.size(); i++) {
    setOperand(idxList[i], i + 1);
  }
  elementType_ = computeElementType(ptr, idxList);
  insertedBlock->addInstruction(this);
}

GetElementPtrInst *GetElementPtrInst::Create(Context &context, Value *ptr,
                                             std::vector<Value *> idxList,
                                             BasicBlock *insertedBlock,
                                             std::string name) {
  std::vector<Value *> temp;
  for (auto i : idxList) {
    if (dynamic_cast<ConstantInt*>(i)) {
      temp.emplace_back(ConstantInt::get(context, Type::getInt32Type(context), dynamic_cast<ConstantInt*>(i)->getValue()));
    } else {
      temp.emplace_back(i);
    }
  }
  return new GetElementPtrInst(context, ptr, temp, insertedBlock, name);
}

Type *GetElementPtrInst::computeElementType(Value *ptr,
                                            std::vector<Value *> idxList) {
  Type *elementType = ptr->getType()->getPtrElementType();
  assert("GetElementPtrInst ptr is wrong type" &&
         (elementType->isArrayType() || elementType->isIntegerType() ||
          elementType->isFloatType() || elementType->isPointerType() ));
  if (elementType->isArrayType()) {
    ArrayType *arr_ty = static_cast<ArrayType *>(elementType);
    for (int i = 1; i < idxList.size(); i++) {
      elementType = arr_ty->getElementType();
      if (elementType->isArrayType()) {
        arr_ty = static_cast<ArrayType *>(elementType);
      }
    }
  } else if (elementType->isPointerType()) {
    ArrayType *arr_ty = static_cast<ArrayType *>(elementType->getPtrElementType());
    for (int i = 1; i < idxList.size(); i++) {
      elementType = arr_ty->getElementType();
      if (elementType->isArrayType()) {
        arr_ty = static_cast<ArrayType *>(elementType);
      }
    }
  }
  return elementType;
}

Type *GetElementPtrInst::getElementType() { return elementType_; }

std::string GetElementPtrInst::print() {
  std::string IR;
  char IRtemp[100];
  // <result> = getelementptr <type>, <type>* <ptrval> [, <type> <idx>]
  std::string fmt("%%%s = getelementptr %s, ");
  assert(getOperandType(0)->isPointerType());
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                getOperandType(0)->getPtrElementType()->getTypeName().c_str());
  IR.assign(IRtemp);
  for (int i = 0; i < getOperandNum(); i++) {
    if (i > 0)
      IR += ", ";
    IR += getOperand(i)->getType()->getTypeName() + " " +
          print_as_op(getOperand(i));
  }
  return IR;
}

IcmpInst::IcmpInst(Context &c, Type *type, IcmpOp icmpOp, Value *leftValue,
                   Value *rightValue, BasicBlock *insertedBlock, std::string name)
    : Instruction(c, type, InstId::Icmp, 2, insertedBlock, name), icmpOp_(icmpOp) {
  setOperand(leftValue, 0);
  setOperand(rightValue, 1);
  insertedBlock->addInstruction(this);
}

IcmpInst *IcmpInst::Create(Context &context, IcmpOp icmpOp, Value *leftValue,
                           Value *rightValue, BasicBlock *insertedBlock, std::string name) {
  return new IcmpInst(context, Type::getInt1Type(context), icmpOp, leftValue, rightValue,
                      insertedBlock, name);
}

std::string IcmpInst::getIcmpOpName() {
  std::string icmpOpName;
  switch (icmpOp_) {
  case IcmpOp::EQ:
    icmpOpName = "eq";
    break;
  case IcmpOp::NEQ:
    icmpOpName = "ne";
    break;
  case IcmpOp::GT:
    icmpOpName = "sgt";
    break;
  case IcmpOp::GTE:
    icmpOpName = "sge";
    break;
  case IcmpOp::LT:
    icmpOpName = "slt";
    break;
  case IcmpOp::LTE:
    icmpOpName = "sle";
    break;
  default:
    icmpOpName = "icmpOp error";
    break;
  }
  return icmpOpName;
}

IcmpInst::IcmpOp IcmpInst::getIcmpOp() { return icmpOp_; }

std::string IcmpInst::print() {
  std::string IR;
  char IRtemp[256];
  if (getOperandType(0) == getOperandType(1)) {
    // <result> = icmp <cond> <type> <op1>, <op2>
    std::string fmt("%%%s = icmp %s %s %s, %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                  getIcmpOpName().c_str(), getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str(),
                  print_as_op(getOperand(1)).c_str());
  } else {
    // <result> = icmp <cond> <type> <op1>, <type> <op2>
    std::string fmt("%%%s = icmp %s %s %s, %s %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                  getIcmpOpName().c_str(), getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str(),
                  getOperandTypeName(1).c_str(),
                  print_as_op(getOperand(1)).c_str());
  }
  IR.assign(IRtemp);
  return IR;
}

LoadInst::LoadInst(Context &c, Type *type, Value *ptr, BasicBlock *insertedBlock, std::string name)
    : Instruction(c, type, InstId::Load, 1, insertedBlock, name) {
  setOperand(ptr, 0);
  insertedBlock->addInstruction(this);
}

LoadInst *LoadInst::Create(Context &c, Type *type, Value *ptr, BasicBlock *insertedBlock, std::string name) {
  return new LoadInst(c, type, ptr, insertedBlock, name);
}

LoadInst *LoadInst::Create(Context &c, Value *ptr, BasicBlock *insertedBlock, std::string name) {
  assert(ptr->getType()->isPointerType());
  return new LoadInst(c, ptr->getType()->getPtrElementType(), ptr, insertedBlock, name);
}



std::string LoadInst::print() {
  std::string IR;
  char IRtemp[100];
  // <result> = load <type>, <type>* <pointer>
  std::string fmt("%%%s = load %s, %s %s");
  assert(getOperandType(0)->isPointerType());
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                getOperandType(0)->getPtrElementType()->getTypeName().c_str(),
                getOperandTypeName(0).c_str(),
                print_as_op(getOperand(0)).c_str());
  IR.assign(IRtemp);
  return IR;
}

PhiInst::PhiInst(Context &c, Type *type,
                 std::vector<std::pair<Value *, BasicBlock *>> valAndLabels,
                 BasicBlock *insertedBlock, std::string name)
    : Instruction(c, type, InstId::Phi, 2 * valAndLabels.size(), insertedBlock, name) {
  for (int i = 0; i < valAndLabels.size(); i++) {
    setOperand(valAndLabels[i].first, 2 * i);
    setOperand(valAndLabels[i].second, 2 * i + 1);
  }
  // insertedBlock->addInstruction(this);
}

PhiInst* PhiInst::Create(Context &c, Type *type,
                std::vector<std::pair<Value *, BasicBlock *>> valAndLabels,
                BasicBlock *insertedBlock, std::string name) {
  return new PhiInst(c, type, valAndLabels, insertedBlock, name);
}

PhiInst* PhiInst::Create(Context &c, Type *type, BasicBlock *insertedBlock, std::string name) {
  std::vector<std::pair<Value *, BasicBlock *>> valAndLabels;
  return new PhiInst(c, type, valAndLabels, insertedBlock, name);
}

std::string PhiInst::print() {
  std::string IR;
  char IRtemp[100];
  // <result> = phi <ty> [ <val0>, <label0>], ...
  std::string fmt("%%%s = phi %s ");
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                getOperandType(0)->getTypeName().c_str());
  IR.assign(IRtemp);
  for (int i = 0; i < getOperandNum() / 2; i++) {
    if (i > 0)
      IR += ", ";
    IR += "[ ";
    IR += print_as_op(getOperand(2 * i));
    IR += ", ";
    IR += print_as_op(getOperand(2 * i + 1));
    IR += " ]";
  }
  return IR;
}

ReturnInst::ReturnInst(Context &context, BasicBlock *insertedBlock)
    : Instruction(Type::getVoidType(context), InstId::Ret, 0, insertedBlock) {
  assert(insertedBlock != nullptr);
  insertedBlock->addInstruction(this);
}

ReturnInst::ReturnInst(Context &context, Value *value,
                       BasicBlock *insertedBlock)
    : Instruction(Type::getVoidType(context), InstId::Ret, 1, insertedBlock) {
  assert(insertedBlock != nullptr);
  insertedBlock->addInstruction(this);
  setOperand(value, 0);
}

ReturnInst *ReturnInst::Create(Context &context, BasicBlock *insertedBlock) {
  assert(insertedBlock != nullptr);
  return new ReturnInst(context, insertedBlock);
}

ReturnInst *ReturnInst::Create(Context &context, Value *retVal,
                               BasicBlock *insertedBlock) {
  assert(insertedBlock != nullptr);
  return new ReturnInst(context, retVal, insertedBlock);
}

bool ReturnInst::isRetVoid() { return getOperandNum() == 0; }

std::string ReturnInst::print() {
  std::string IR;
  char IRtemp[100];
  if (!isRetVoid()) {
    // ret <type> <value>
    std::string fmt("ret %s %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(),
                  getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str());
  } else {
    // ret void
    return std::string("ret void");
  }
  IR.assign(IRtemp);
  return IR;
}

SiToFpInst::SiToFpInst(Context &c, Type *destType, Value *value, BasicBlock *insertedBlock, std::string name)
    : Instruction(c, destType, InstId::Sitofp, 1, insertedBlock, name),
      destType_(destType) {
  setOperand(value, 0);
  insertedBlock->addInstruction(this);
}

SiToFpInst *SiToFpInst::Create(Context &c, Type *destType, Value *value,
                               BasicBlock *insertedBlock, std::string name) {
  return new SiToFpInst(c, destType, value, insertedBlock, name);
}

Type *SiToFpInst::getDestType() { return destType_; }

std::string SiToFpInst::print() {
  std::string IR;
  char IRtemp[100];
  // <result> = sitofp <type> <value> to <type2>
  std::string fmt("%%%s = sitofp %s %s to %s");
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                getOperandType(0)->getTypeName().c_str(),
                print_as_op(getOperand(0)).c_str(),
                destType_->getTypeName().c_str());
  IR.assign(IRtemp);
  return IR;
}

StoreInst::StoreInst(Context &context, Value *value, Value *ptr,
                     BasicBlock *insertedBlock)
    : Instruction(Type::getVoidType(context), InstId::Store, 2, insertedBlock) {
  setOperand(value, 0);
  setOperand(ptr, 1);
  insertedBlock->addInstruction(this);
}

StoreInst *StoreInst::Create(Context &context, Value *value, Value *ptr,
                             BasicBlock *insertedBlock) {
  return new StoreInst(context, value, ptr, insertedBlock);
}

std::string StoreInst::print() {
  std::string IR;
  char IRtemp[100];
  // store <type> <value>, <type>* <pointer>
  std::string fmt("store %s %s, %s %s");
  std::snprintf(
      IRtemp, sizeof IRtemp, fmt.c_str(), getOperandTypeName(0).c_str(),
      print_as_op(getOperand(0)).c_str(), getOperandTypeName(1).c_str(),
      print_as_op(getOperand(1)).c_str());
  IR.assign(IRtemp);
  return IR;
}

UnaryInst::UnaryInst(Context &c, Type *type, InstId instId, Value *rightValue,
                     BasicBlock *insertedBlock, std::string name)
    : Instruction(c, type, instId, 1, insertedBlock, name) {
  setOperand(rightValue, 0);
  insertedBlock->addInstruction(this);
}

UnaryInst *UnaryInst::CreateNegative(Context &context, Value *rightValue,
                                     BasicBlock *insertedBlock,
                                     std::string name) {
  return new UnaryInst(context, rightValue->getType(), InstId::Negative,
                       rightValue, insertedBlock, name);
}
UnaryInst *UnaryInst::CreateNot(Context &context, Value *rightValue,
                                BasicBlock *insertedBlock, std::string name) {
  return new UnaryInst(context, Type::getInt1Type(context), InstId::Not,
                       rightValue, insertedBlock, name);
}

std::string UnaryInst::print() {
  std::string IR;
  char IRtemp[256];
  // <result> = <not/negative> <type> <op1>
  std::string fmt("%%%s = %s %s %s");
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                getInstructionOpName().c_str(), getOperandTypeName(0).c_str(),
                print_as_op(getOperand(0)).c_str());
  IR.assign(IRtemp);
  return IR;
}

ZextInst::ZextInst(Context &c, Type *destType, Value *value, BasicBlock *insertedBlock, std::string name)
    : Instruction(c, destType, InstId::Zext, 1, insertedBlock, name),
      destType_(destType) {
  setOperand(value, 0);
  insertedBlock->addInstruction(this);
}

ZextInst *ZextInst::Create(Context &c, Type *destType, Value *value,
                           BasicBlock *insertedBlock, std::string name) {
  return new ZextInst(c, destType, value, insertedBlock, name);
}

Type *ZextInst::getDestType() { return destType_; }

std::string ZextInst::print() {
  std::string IR;
  char IRtemp[100];
  // <result> = zext <type> <value> to <type2>
  std::string fmt("%%%s = zext %s %s to %s");
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                getOperandType(0)->getTypeName().c_str(),
                print_as_op(getOperand(0)).c_str(),
                destType_->getTypeName().c_str());
  IR.assign(IRtemp);
  return IR;
}