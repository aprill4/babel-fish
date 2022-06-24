#pragma once
#include "Instruction.h"

class LoadInst : Instruction {
public:
  LoadInst(Type *ty, Value *ptr, BasicBlock *bb);
  Value *getLval();
  Type *getLoadType();
  std::string print() override;
private:
};