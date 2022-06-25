#pragma once
#include "Instruction.h"

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