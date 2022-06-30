#pragma once

#include "Instruction.h"

class ZextInst : public Instruction {
public:
  ZextInst(Context &c, Type *destType, Value *value, BasicBlock *insertedBlock, std::string name);
  Type *getDestType();
  std::string print() override;

public:
  static ZextInst *Create(Context &c, Type *destType, Value *value,
                          BasicBlock *insertedBlock, std::string name = "v");

private:
  Type *destType_;
};
