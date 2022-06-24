#pragma once
#include "Instruction.h"

class ReturnInst : public Instruction {
public:
  ReturnInst(Value *val, BasicBlock *bb);
  ReturnInst(BasicBlock *bb);
  bool isVoidRet();
  std::string print() override;

private:
};