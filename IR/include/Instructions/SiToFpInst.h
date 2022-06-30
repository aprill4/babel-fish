#pragma once

#include "Instruction.h"

class SiToFpInst : public Instruction {
public:
  SiToFpInst(Context &c, Type *destType, Value *value, BasicBlock *insertedBlock, std::string name);
  Type *getDestType();
  std::string print() override;

public:
  static SiToFpInst *Create(Context &c, Type *destType, Value *value,
                            BasicBlock *insertedBlock, std::string name = "v");

private:
  Type *destType_;
};