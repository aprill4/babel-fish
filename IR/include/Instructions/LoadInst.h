#pragma once
#include "Instruction.h"

class LoadInst : public Instruction {
public:
  LoadInst(Type *type, Value *ptr, BasicBlock *insertedBlock);
  std::string print() override;

public:
  static LoadInst *Create(Type *type, Value *ptr, BasicBlock *insertedBlock);

private:
};