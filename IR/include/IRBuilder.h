#pragma once
#include "IR.h"

class IRBuilder {
public:
  IRBuilder()
      : context_(*new Context()), module_(new Module(context_, "main_module")) {
  }

public:
  Module *getModule() { return module_; }
  Context &getContext() { return context_; }
  //void setTmpVal(Value *val) { tmp_ = val; }

private:
  //Value *tmp_;
  Context &context_;
  Module *module_;
};