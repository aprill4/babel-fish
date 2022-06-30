#pragma once

#include "Instruction.h"

class AllocaInst : public Instruction {
public:
  AllocaInst(Context &context, Type *allocaType, BasicBlock *insertedBlock, std::string name);
  Type *getAllocaType();
  std::string print() override;

public:
  static AllocaInst *Create(Context &context, Type *allocaType,
                                   BasicBlock *insertedBlock, std::string name = "v");

private:
  Type *allocaType_;
};