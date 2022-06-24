#pragma once

#include "Instruction.h"

class BranchInst : public Instruction {
public:
  BranchInst(Value *cond, BasicBlock *if_true, BasicBlock *if_false,
             BasicBlock *bb);
  BranchInst(BasicBlock *if_true, BasicBlock *bb);
  bool isCondBr();
  std::string print() override;
};
