#pragma once
#include "Instruction.h"

class StoreInst : public Instruction {
public:
  StoreInst(Context &context, Value *value, Value *ptr,
            BasicBlock *insertedBlock);
  std::string print() override;

public:
  static StoreInst *Create(Context &context, Value *value, Value *ptr,
                           BasicBlock *insertedBlock);
private:
};