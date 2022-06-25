#pragma once

#include "Instruction.h"

class FunctionType;
class Function;

class CallInst : public Instruction {
public:
  CallInst(Function *func, std::vector<Value *> funcArgs,
           BasicBlock *insertedBlock);
  FunctionType *getFunctionType();
  std::string print() override;

public:
  static CallInst *Create(Function *func, std::vector<Value *> funcArgs,
                          BasicBlock *insertedBlock);

private:
};
