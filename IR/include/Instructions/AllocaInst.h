#pragma once

#include "Instruction.h"

class AllocaInst : public Instruction {
public:
  AllocaInst(Type *ty, BasicBlock *bb);
  //   static AllocaInst *create_alloca(Type *ty, BasicBlock *bb);
  Type *getAllocaType();
  std::string print() override;

private:
  Type *allocaType_;
};