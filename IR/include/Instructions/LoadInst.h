#pragma once
#include "Instruction.h"

class LoadInst : public Instruction {
public:
  LoadInst(Context &c, Type *type, Value *ptr, BasicBlock *insertedBlock);
  std::string print() override;

public:
  static LoadInst *Create(Context &c, Type *type, Value *ptr, BasicBlock *insertedBlock);

private:
};