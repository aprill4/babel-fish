#pragma once
#include "Instruction.h"

class FpToSiInst : public Instruction {
public:
  FpToSiInst(Type *destType, Value *value, BasicBlock *insertedBlock);
  Type *getDestType();
  std::string print() override;

public:
  static FpToSiInst *Create(Type *destType, Value *value,
                            BasicBlock *insertedBlock);

private:
  Type *destType_;
};