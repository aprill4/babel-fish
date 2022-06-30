#pragma once
#include "Instruction.h"

class FpToSiInst : public Instruction {
public:
  FpToSiInst(Context &c, Type *destType, Value *value, BasicBlock *insertedBlock);
  Type *getDestType();
  std::string print() override;

public:
  static FpToSiInst *Create(Context &c, Type *destType, Value *value,
                            BasicBlock *insertedBlock);

private:
  Type *destType_;
};