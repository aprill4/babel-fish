#pragma once
#include "Instruction.h"

class BinaryInst : public Instruction {
public:
  BinaryInst(Type *type, OpId opId, Value *valueL, Value *valueR,
             BasicBlock *bb);
  std::string print() override;

private:
};