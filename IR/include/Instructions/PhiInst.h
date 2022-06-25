#pragma once

#include "Instruction.h"

class PhiInst : public Instruction {
public:
  PhiInst(Type *type,
          std::vector<std::pair<Value *, BasicBlock *>> valAndLabels,
          BasicBlock *insertedBlock);
  std::string print() override;

public:
  static PhiInst *
  Create(Type *type, std::vector<std::pair<Value *, BasicBlock *>> valAndLabels,
         BasicBlock *insertedBlock);

private:
};