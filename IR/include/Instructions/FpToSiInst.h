#pragma once
#include "Instruction.h"

class FpToSiInst : public Instruction {
public:
  FpToSiInst(Context &c, Type *destType, Value *value, BasicBlock *insertedBlock, std::string name);
  Type *getDestType();
  std::string print() override;

public:
  static FpToSiInst *Create(Context &c, Type *destType, Value *value,
                            BasicBlock *insertedBlock, std::string name = "v");

private:
  Type *destType_;
};