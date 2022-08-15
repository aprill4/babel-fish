#pragma once

#include <iostream>
#include <algorithm>
#include "Exception.h"
#include <iterator>
#include <vector>
#include <string>
#include <utility>
#include <list>
#include <memory>
#include <set>
#include <map>
#include <stdio.h>
#include <cassert>

class Context;

class Type;
class IntegerType;
class PointerType;
class ArrayType;
class FunctionType;

class Value;
class Use;
class User;

class Constant;
class ConstantInt;
class ConstantFloat;
class ConstantZero;
class ConstantArray;
class Argument;

class Module;
class Function;
class GlobalVariable;
class BasicBlock;
class Instruction;

class AllocaInst;
class BinatyInst;
class BranchInst;
class CallInst;
class FcmpInst;
class FpToSiInst;
class GetElementPtrInst;
class IcmpInst;
class LoadInst;
class PhiInst;
class ReturnInst;
class SiToFpInst;
class StoreInst;
class UnaryInst;

class Util;

class Context {
public:
  Context();
  ~Context();

  Module *ownerModule;

  Type *VoidType, *LabelType, *FloatType;
  IntegerType *Int1Type, *Int32Type;

  std::map<std::pair<Type *, std::size_t>, ArrayType *> ArrayTypes;
  std::map<Type *, PointerType *> PointerTypes;

  void addModule(Module *module);

  PointerType *getPtrType(Type *ptrElementType);
  ArrayType *getArrayType(Type *elementType, std::size_t elementNum);

  size_t counter = 0;
private:
};

class Type {
public:
  enum TypeId {
    VoidTypeId,
    FloatTypeId,
    IntegerTypeId,
    FunctionTypeId,
    ArrayTypeId,
    LabelTypeId,
    PointerTypeId
  };

public:
  explicit Type(TypeId typdId);
  ~Type() = default;
  bool operator==(const Type &type);

  TypeId getTypeId() { return typeId_; }

  bool isVoidType() { return typeId_ == TypeId::VoidTypeId; }
  bool isFloatType() { return typeId_ == TypeId::FloatTypeId; }
  bool isIntegerType() { return typeId_ == TypeId::IntegerTypeId; }
  bool isFunctionType() { return typeId_ == TypeId::FunctionTypeId; }
  bool isArrayType() { return typeId_ == TypeId::ArrayTypeId; }
  bool isLabelType() { return typeId_ == TypeId::LabelTypeId; }
  bool isPointerType() { return typeId_ == TypeId::PointerTypeId; }

  std::string getTypeName();
  Type *getPtrElementType();

  static Type *getVoidType(Context &context);
  static Type *getLabelType(Context &context);
  static Type *getFloatType(Context &context);
  static IntegerType *getInt1Type(Context &context);
  static IntegerType *getInt32Type(Context &context);
  static PointerType *getPtrType(Context &context, Type *ptrElementType);
  static ArrayType *getArrayType(Context &context, Type *elementType,
                                 std::size_t elementNum);
  // static PointerType *getFloatPtrType(Context& context);

  TypeId typeId_;
};

class IntegerType : public Type {
public:
  explicit IntegerType(std::size_t bitsNum);
  std::size_t getBitsNum();
  IntegerType *get(std::size_t bitsNum);

private:
  std::size_t bitsNum_;
};

class PointerType : public Type {
public:
  PointerType(Type *ptrElementType);
  Type *getPtrElementType();

public:
  static PointerType *get(Context &context, Type *ptrElementType);

private:
  Type *ptrElementType_;
};

class ArrayType : public Type {
public:
  ArrayType(Type *elementType, std::size_t elementNum);
  Type *getElementType();
  std::size_t getElementNum();
  std::size_t getAllElementNum();

public:
  static ArrayType *get(Context &context, Type *elementType,
                        std::size_t elementNum);
  static ArrayType *get(Context &context, Type *elementType,
                        std::vector<int> dimension);
  Type *elementType_;
  //total number of elements, -1 is reserved for the situation when the first dimension is unknown 
  std::size_t elementNum_;
};

class FunctionType : public Type {
public:
  FunctionType(Type *resultType);
  FunctionType(Type *resultType, std::vector<Type *> argumentsType_);
  static FunctionType *get(Type *resultType);
  static FunctionType *get(Type *resultType, std::vector<Type *> paramsType);
  std::size_t getArgumentsNum();
  Type *getReturnType();
  Type *getArgumentType(std::size_t idx);

private:
  Type *resultType_;
  std::vector<Type *> argumentsType_;
};

class Value {
public:
  explicit Value(Type *type, const std::string &name = "");
  explicit Value(Context &c, Type *type, const std::string &name = "");

  virtual ~Value() = default;

  Type *getType();

  bool setName(const std::string &name);
  std::string getName();
  std::string getLLVM_Name();

  void addUse(const Use &u);
  void addUse(Value *val, unsigned no = 0);
  void removeUse(Value *val);
  virtual std::string print() = 0;
  size_t getNO();
  void replaceAllUseWith(Value *new_val);

  Type *type_;
  std::string name_;
  std::list<Use> useList_;
  size_t no_;
};

class Use {
public:
  Use(Value* user_, unsigned no);
  Value *getUser();
  unsigned getNo() { return no_;}
private:
  Value *user_ = nullptr;
  unsigned no_;
};

class User : public Value {
public:
  User(Type *type, const std::string &name = "", std::size_t operandNum = 0);
  User(Context &c, Type *type, const std::string &name = "", std::size_t operandNum = 0);

  std::size_t getOperandNum();
  Value *getOperand(std::size_t idx);
  Type *getOperandType(std::size_t idx);
  std::string getOperandTypeName(std::size_t idx);
  void addOperand(Value *v);
  void setOperand(Value* value, std::size_t idx);
  void removeUseOfOps(){
    for (auto op : operands_) {
      op->removeUse(this);
    }
  }
public:
  std::vector<Value *> operands_;
  std::size_t operandNum_;
};

class Constant : public User {
public:
  Constant(Context &c, Type *type, const std::string &name = "", std::size_t operandNum = 0)
      : User(c, type, name, operandNum) {}
};

class ConstantInt : public Constant {
public:
  ConstantInt(Context &c, Type *type, int32_t value)
      : Constant(c, type, "", 0), value_(value) {}
  ssize_t getValue() { return value_; }
  void setValue(int32_t value) { value_ = value; }
  std::string print() override;

public:
  static ConstantInt *get(Context &c, Type *type, int32_t value) {
    return new ConstantInt(c, type, value);
  }

  int32_t value_;
};

class ConstantFloat : public Constant {
public:
  ConstantFloat(Context &c, Type *type, float value)
      : Constant(c, type, "", 0), value_(value) {}
  float getValue() { return value_; }
  void setValue(float value) { value_ = value; }
  std::string print() override;

public:
  static ConstantFloat *get(Context &context, float value);

  float value_;
};

class ConstantZero : public Constant {
public:
  ConstantZero(Context &c, Type *type) : Constant(c, type, "", 0) {}
  std::string print() override;

public:
  static ConstantZero *get(Context &c, Type *type);

private:
};

class ConstantArray : public Constant {
public:
  ConstantArray(Context &c, ArrayType *type, const std::vector<Value *> &value, const std::vector<int> &dimension);
  Value *getElementValue(int idx);
  std::string print() override;

public:
  static ConstantArray *get(Context &c, ArrayType *type,
                            const std::vector<Value *> &value,
                            const std::vector<int> &dimension);

public:
  std::vector<Value *> value_;
  //to locate the element from indice(format: e.g. const int a[1][2][3] ,dimensions_ = {1, 2, 3})
  std::vector<int> dimension_;
};

class Argument : public Value {
public:
  Argument(Context &c, Type *type, const std::string &name = "", Function *f = nullptr,
           std::size_t argumentNo = 0);
  Function *getFucntion() { return parent_; }
  std::size_t getArgumentNo() const { return argumentNo_; }
  std::string print() override;

private:
  Function *parent_;
  std::size_t argumentNo_;
};

class Module {
public:
  Module(Context &context, const std::string &moduleName);
  void addFuntion(Function *func);
  void addGlobalVariable(GlobalVariable *globalVariable);
  void delete_dead_block();
  std::string print();

  Context &context_;
  std::string moduleName_;
  std::set<GlobalVariable *> globalVariableList_;
  std::vector<Function *> functionList_;
  std::map<std::string, Value *> symbolTable_; // we could replace above two STL with this map
};

class Function : public Value {
public:
  Function(Context &c, FunctionType *funcType, const std::string args_name[], const std::string &funcName, Module *parent, bool is_decl = false, bool inLib = false);

  Module *getModule();
  Type *getReturnType();

  std::size_t getArgumentsNum();
  FunctionType *getFunctionType();

  void addBasicBlock(BasicBlock *bb);
  std::list<BasicBlock *>& getBasicBlocks();
  BasicBlock *getEntryBlock() { return *basicBlocks_.begin(); }
  void remove(BasicBlock* bb);
  Argument *getArgument(size_t idx);

  std::string print() override;

public:
  static Function *Create(Context &c, FunctionType *funcType, const std::string args_name[], const std::string &funcName,
                          Module *parent, bool is_decl = false, bool inLib = false);
  bool is_declaration;
  bool is_libFn;
  Module *parent_;
  std::string name_;
  std::list<BasicBlock *> basicBlocks_;
  std::vector<Argument *> arguments_; // formalArgs
};

class GlobalVariable : public User {
public:
  GlobalVariable(Context &c, Type *type, const std::string &globalVarName, bool isConst,
                 Constant *initializer, Module *insertedModule);
  std::string print() override;
  bool isConst() { return isConst_; }
  Constant *getInitValue() { return initValue_; }

public:
  static GlobalVariable *Create(Context &c, Type *type, const std::string &globalVarName,
                                bool isConst, Constant *initializer,
                                Module *insertedModule);

private:
  Constant *initValue_;
  bool isConst_;
};

class BasicBlock : public Value {
public:
  BasicBlock(Context &context, const std::string &name, Function *parent);
  ~BasicBlock();
  Module *getModule();
  std::string print() override;

  void addInstruction(Instruction *instruction);
  void addPredecessor(BasicBlock* pre);
  void addSuccessor(BasicBlock* suc);

  void addDominator(BasicBlock *dom);
  void setDominators(std::set<BasicBlock *> &doms);
  std::set<BasicBlock *>& getDominators();

  std::list<BasicBlock *>& getSuccessor();
  std::list<BasicBlock *>& getPredecessors();

  bool hasTerminator();
  void eraseFromParent();

  void addInstInBegin(Instruction *inst) {
    instructionList_.push_front(inst);
  }

  void deleteInst(Instruction *inst);

public:
  static BasicBlock *Create(Context &context, const std::string &name,
                            Function *parent);

  std::list<Instruction *> instructionList_;
  Function *parent_;
  std::list<BasicBlock *> predecessorBlocks_;
  std::list<BasicBlock *> successorBlocks_;
  std::set<BasicBlock *> dominators_;
};

class Instruction : public User {
public:
  enum InstId {
    Ret,
    Br,
    Add,
    Sub,
    Mul,
    Sdiv,
    Mod,
    Fadd,
    Fsub,
    Fmul,
    Fdiv,
    And,
    Or,
    Alloca,
    Load,
    Store,
    Icmp,
    Fcmp,
    Phi,
    Call,
    Getelementptr,
    Zext,
    Fptosi,
    Sitofp,
    Negative,
    Not,
  };

  Instruction(Type *type, InstId instId, std::size_t operandNum, BasicBlock *parent);
  
  Instruction(Type *type, InstId instId, std::size_t operandNum, BasicBlock *parent, std::string name);

  Instruction(Context &c, Type *type, InstId instId, std::size_t operandNum,
              BasicBlock *parent, std::string name);

  Module *getModule();

  InstId getInstrcutionType() { return instId_; }
  std::string getInstructionOpName();

  bool isPhi();
  bool isStore();
  bool isAlloca();
  bool isRet();
  bool isLoad();
  bool isBr();

  bool isAdd();
  bool isSub();
  bool isMul();
  bool isDiv();
  bool isMod();

  bool isFadd();
  bool isFsub();
  bool isFmul();
  bool isFdiv();

  bool isAnd();
  bool isOr();

  bool isFp2si();
  bool isSi2fp();

  bool isIcmp();
  bool isFcmp();

  bool isCall();
  bool isGep();
  bool isZext();

  bool isVoid();
  bool isBinary();
  bool isNot();
  bool isNegative();
  bool isTerminator();

  BasicBlock *parent_;
  InstId instId_;
};

class AllocaInst : public Instruction {
public:
  AllocaInst(Context &context, Type *allocaType, BasicBlock *insertedBlock, std::string name);
  Type *getAllocaType();
  std::string print() override;

public:
  static AllocaInst *Create(Context &context, Type *allocaType,
                                   BasicBlock *insertedBlock, std::string name = "v");

  Type *allocaType_;
};

class BinaryInst : public Instruction {
public:
  BinaryInst(Context &c, Type *type, InstId instId, Value *leftValue, Value *rightValue,
             BasicBlock *insertedBlock, std::string name);
  std::string print() override;

public:
  static BinaryInst *CreateAdd(Context &context, Value *leftValue,
                               Value *rightValue, BasicBlock *insertedBlock, std::string name = "v");
  static BinaryInst *CreateSub(Context &context, Value *leftValue,
                               Value *rightValue, BasicBlock *insertedBlock, std::string name = "v");
  static BinaryInst *CreateMul(Context &context, Value *leftValue,
                               Value *rightValue, BasicBlock *insertedBlock, std::string name = "v");
  static BinaryInst *CreateSdiv(Context &context, Value *leftValue,
                                Value *rightValue, BasicBlock *insertedBlock, std::string name = "v");
  static BinaryInst *CreateMod(Context &context, Value *leftValue,
                                Value *rightValue, BasicBlock *insertedBlock, std::string name = "v");
  static BinaryInst *CreateFadd(Context &context, Value *leftValue,
                                Value *rightValue, BasicBlock *insertedBlock, std::string name = "v");
  static BinaryInst *CreateFsub(Context &context, Value *leftValue,
                                Value *rightValue, BasicBlock *insertedBlock, std::string name = "v");
  static BinaryInst *CreateFmul(Context &context, Value *leftValue,
                                Value *rightValue, BasicBlock *insertedBlock, std::string name = "v");
  static BinaryInst *CreateFdiv(Context &context, Value *leftValue,
                                Value *rightValue, BasicBlock *insertedBlock, std::string name = "v");
  static BinaryInst *CreateAnd(Context &context, Value *leftValue,
                                Value *rightValue, BasicBlock *insertedBlock, std::string name = "v");
  static BinaryInst *CreateOr(Context &context, Value *leftValue,
                                Value *rightValue, BasicBlock *insertedBlock, std::string name = "v");
private:
};

class BranchInst : public Instruction {
public:
  BranchInst(Context &context, BasicBlock *ifTrueBlock,
             BasicBlock *insertedBlock);
  BranchInst(Context &context, Value *cond, BasicBlock *ifTrueBlock,
             BasicBlock *ifFalseBlock, BasicBlock *insertedBlock);
  bool isCondBr();
  std::string print() override;

public:
  static BranchInst *Create(Context &context, BasicBlock *ifTrueBlock,
                            BasicBlock *insertedBlock);
  static BranchInst *Create(Context &context, Value *cond,
                            BasicBlock *ifTrueBlock, BasicBlock *ifFalseBlock,
                            BasicBlock *insertedBlock);

private:
};

class CallInst : public Instruction {
public:
  CallInst(Context& c, Function *func, std::vector<Value *> funcArgs,
           BasicBlock *insertedBlock, std::string name);
  FunctionType *getFunctionType();
  std::string print() override;

public:
  static CallInst *Create(Context& c, Function *func, std::vector<Value *> funcArgs,
                          BasicBlock *insertedBlock, std::string name = "v");

private:
};

class FcmpInst : public Instruction {
public:
  enum FcmpOp { EQ, NEQ, GT, GTE, LT, LTE };
  FcmpInst(Context &c, Type *type, FcmpOp fcmpOp, Value *leftValue, Value *rightValue,
           BasicBlock *insertedBlock, std::string name);
  FcmpOp getFcmpOp();
  std::string getFcmpOpName();
  std::string print() override;

public:
  static FcmpInst *Create(Context &context, FcmpOp fcmpOp, Value *leftValue,
                          Value *rightValue, BasicBlock *insertedBlock, std::string name = "v");

private:
  FcmpOp fcmpOp_;
};

class FpToSiInst : public Instruction {
public:
  FpToSiInst(Context &c, Type *destType, Value *value, BasicBlock *insertedBlock, std::string name);
  Type *getDestType();
  std::string print() override;

public:
  static FpToSiInst *Create(Context &c, Type *destType, Value *value,
                            BasicBlock *insertedBlock, std::string name = "v");

private:
  Type *destType_;
};

class GetElementPtrInst : public Instruction {
public:
  GetElementPtrInst(Context &context, Value *ptr, std::vector<Value *> idxList,
                    BasicBlock *insertedBlock, std::string name);
  Type *getElementType();
  Type *computeElementType(Value *ptr, std::vector<Value *> idxList);
  std::string print() override;

public:
  static GetElementPtrInst *Create(Context &context, Value *ptr,
                                   std::vector<Value *> idxList,
                                   BasicBlock *insertedBlock, std::string name = "v");

private:
  Type *elementType_;
};

class IcmpInst : public Instruction {
public:
  enum class IcmpOp { EQ, NEQ, GT, GTE, LT, LTE };
  IcmpInst(Context &c, Type *type, IcmpOp icmpOp, Value *leftValue, Value *rightValue,
           BasicBlock *insertedBlock, std::string name);
  IcmpOp getIcmpOp();
  std::string getIcmpOpName();
  std::string print() override;

public:
  static IcmpInst *Create(Context &context, IcmpOp icmpOp, Value *leftValue,
                          Value *rightValue, BasicBlock *insertedBlock, std::string name = "bool_");

private:
  IcmpOp icmpOp_;
};

class LoadInst : public Instruction {
public:
  LoadInst(Context &c, Type *type, Value *ptr, BasicBlock *insertedBlock, std::string name);
  std::string print() override;
  Value *getLval() { return this->getOperand(0); }

public:
  static LoadInst *Create(Context &c, Value *ptr, BasicBlock *insertedBlock, std::string name = "v");
  static LoadInst *Create(Context &c, Type *type, Value *ptr, BasicBlock *insertedBlock, std::string name = "v");

private:
};

class PhiInst : public Instruction {
public:
  PhiInst(Context &c,Type *type,
          std::vector<std::pair<Value *, BasicBlock *>> valAndLabels,
          BasicBlock *insertedBlock, std::string name);
  std::string print() override;
  void setLval(Value *lval) { lval_ = lval; }
  Value *getLval() { return lval_; }
  void add_phi_pair_operand(Value *val, Value *pre_bb) {
    this->addOperand(val);
    this->addOperand(pre_bb);
  }
  std::vector<Value*> getInComingVal();
  std::vector<BasicBlock*> getInComingBlock();
public:
  static PhiInst *
  Create(Context &c, Type *type, std::vector<std::pair<Value *, BasicBlock *>> valAndLabels,
         BasicBlock *insertedBlock, std::string name = "v");
  static PhiInst *
  Create(Context &c, Type *type, BasicBlock *insertedBlock, std::string name = "v");

private:
  Value *lval_;

};

class ReturnInst : public Instruction {
public:
  ReturnInst(Context &context, BasicBlock *insertedBlock);
  ReturnInst(Context &context, Value *retValue, BasicBlock *insertedBlock);
  bool isRetVoid();
  std::string print() override;

public:
  static ReturnInst *Create(Context &context, BasicBlock *insertedBlock);
  static ReturnInst *Create(Context &context, Value *retValue,
                            BasicBlock *insertedBlock);

private:
};

class SiToFpInst : public Instruction {
public:
  SiToFpInst(Context &c, Type *destType, Value *value, BasicBlock *insertedBlock, std::string name);
  Type *getDestType();
  std::string print() override;

public:
  static SiToFpInst *Create(Context &c, Type *destType, Value *value,
                            BasicBlock *insertedBlock, std::string name = "v");

private:
  Type *destType_;
};

class StoreInst : public Instruction {
public:
  StoreInst(Context &context, Value *value, Value *ptr,
            BasicBlock *insertedBlock);
  std::string print() override;
  Value *getRval() { return this->getOperand(0); }
  Value *getLval() { return this->getOperand(1); }

public:
  static StoreInst *Create(Context &context, Value *value, Value *ptr,
                           BasicBlock *insertedBlock);
  // value,ptr means the rhs and lhs of the assignment respectively
private:
};

class UnaryInst : public Instruction {
public:
  UnaryInst(Context &c, Type *type, InstId instId, Value *rightValue,
            BasicBlock *insertedBlock, std::string name);
  std::string print() override;

public:
  static UnaryInst *CreateNegative(Context &context, Value *rightValue,
                              BasicBlock *insertedBlock,
                              std::string name = "v");
  static UnaryInst *CreateNot(Context &context, Value *rightValue,
                              BasicBlock *insertedBlock,
                              std::string name = "v");
};

class ZextInst : public Instruction {
public:
  ZextInst(Context &c, Type *destType, Value *value, BasicBlock *insertedBlock, std::string name);
  Type *getDestType();
  std::string print() override;

public:
  static ZextInst *Create(Context &c, Type *destType, Value *value,
                          BasicBlock *insertedBlock, std::string name = "v");

private:
  Type *destType_;
};

inline std::string print_as_op(Value *v) {
  std::string op_ir;
  if (dynamic_cast<GlobalVariable *>(v)) {
    op_ir += "@" + v->getLLVM_Name();
  } else if (dynamic_cast<Function *>(v)) {
    op_ir += "@" + v->getName();
  } else if (dynamic_cast<Constant *>(v)) {
    op_ir += v->print();
  } else {
    op_ir += "%" + v->getLLVM_Name();
  }
  return op_ir;
}