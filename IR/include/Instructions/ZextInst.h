#pragma once

#include "Instruction.h"

class ZextInst : public Instruction {
public:
  ZextInst(Type *destType, Value *value, BasicBlock *insertedBlock);
  Type *getDestType();
  std::string print() override;

public:
  static ZextInst *Create(Type *destType, Value *value,
                          BasicBlock *insertedBlock);

private:
  Type *destType_;
};
