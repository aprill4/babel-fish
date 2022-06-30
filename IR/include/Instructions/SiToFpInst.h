#pragma once

#include "Instruction.h"

class SiToFpInst : public Instruction {
public:
  SiToFpInst(Context &c, Type *destType, Value *value, BasicBlock *insertedBlock);
  Type *getDestType();
  std::string print() override;

public:
  static SiToFpInst *Create(Context &c, Type *destType, Value *value,
                            BasicBlock *insertedBlock);

private:
  Type *destType_;
};