#pragma once
#include "IR.h"

class IRBuilder {
public:
  IRBuilder()
      : context_(*new Context()), module_(new Module(context_, "main_module")), current_scope(nullptr) {
  }

public:
  Module *getModule() { return module_; }
  Context &getContext() { return context_; }
  Scope *getScope() { return scope_; }
  BasicBlock *getBasicBlock() { return basicblock_; }

  void setScope(Scope *scope) { scope_ = scope; }
  void setBasicBlock(BasicBlock *basicblock) { basicblock_ = basicblock; }
  //void setTmpVal(Value *val) { tmp_ = val; }

private:
  //Value *tmp_;
  Context &context_;
  Module *module_;
  Scope *scope_;
  BasicBlock *basicblock_; 
};