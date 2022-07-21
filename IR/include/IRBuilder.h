#pragma once
#include "IR.h"

class Scope;
class IRBuilder {
public:
  IRBuilder()
      : context_(*new Context()), module_(new Module(context_, "main_module")),
        scope_(nullptr), basicblock_(nullptr) {}

public:
  Module *getModule() { return module_; }
  Context &getContext() { return context_; }
  Scope *getScope() { return scope_; }
  BasicBlock *getBasicBlock() { return basicblock_; }
  BasicBlock *getWhileBlock() { return whileBlock_; }
  BasicBlock *getNextBlock() { return nextBlock_; }
  Value *getTmpVal() { return val_; }
  Function *getFunction() { return func_; }

  void setScope(Scope *scope) { scope_ = scope; }
  void setBasicBlock(BasicBlock *basicblock) { basicblock_ = basicblock; }
  void setWhileBlock(BasicBlock *whileBlock) { whileBlock_ = whileBlock; }
  void setNextBlock(BasicBlock *nextBlock) { nextBlock_ = nextBlock; }
  void setTmpVal(Value *val) { val_ = val; }
  void setFunction(Function *func) { func_ = func; }

private:
  Value *val_;
  Context &context_;
  Module *module_;
  Scope *scope_;
  BasicBlock *basicblock_;
  BasicBlock *whileBlock_;
  BasicBlock *nextBlock_;
  Function *func_;
};