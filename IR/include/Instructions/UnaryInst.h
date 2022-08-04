#pragma once
#include "Instruction.h"

class UnaryInst : public Instruction {
public:
  UnaryInst(Context &c, Type *type, InstId instId, Value *rightValue,
            BasicBlock *insertedBlock, std::string name);
  std::string print() override;

public:
  static UnaryInst *CreateNegative(Context &context, Value *rightValue,
                              BasicBlock *insertedBlock,
                              std::string name = "v");
  static UnaryInst *CreateNot(Context &context, Value *rightValue,
                              BasicBlock *insertedBlock,
                              std::string name = "v");
};