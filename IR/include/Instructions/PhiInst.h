#pragma once

#include "Instruction.h"

class PhiInst : public Instruction {
public:
  PhiInst(Context &c,Type *type,
          std::vector<std::pair<Value *, BasicBlock *>> valAndLabels,
          BasicBlock *insertedBlock);
  std::string print() override;

public:
  static PhiInst *
  Create(Context &c, Type *type, std::vector<std::pair<Value *, BasicBlock *>> valAndLabels,
         BasicBlock *insertedBlock);

private:
};