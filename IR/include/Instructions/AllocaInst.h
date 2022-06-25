#pragma once

#include "Instruction.h"

class AllocaInst : public Instruction {
public:
  AllocaInst(Context &context, Type *allocaType, BasicBlock *insertedBlock);
  Type *getAllocaType();
  std::string print() override;

public:
  static AllocaInst *Create(Context &context, Type *allocaType,
                                   BasicBlock *insertedBlock);

private:
  Type *allocaType_;
};