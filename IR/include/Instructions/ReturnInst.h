#pragma once
#include "Instruction.h"

class ReturnInst : public Instruction {
public:
  ReturnInst(BasicBlock *bb);
  ReturnInst(Value *val, BasicBlock *bb);
  bool isVoidRet();
  std::string print() override;

private:
};