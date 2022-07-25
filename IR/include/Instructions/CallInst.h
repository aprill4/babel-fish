#pragma once

#include "Instruction.h"

class FunctionType;
class Function;

class CallInst : public Instruction {
public:
  CallInst(Context& c, Function *func, std::vector<Value *> funcArgs,
           BasicBlock *insertedBlock, std::string name);
  FunctionType *getFunctionType();
  std::string print() override;

public:
  static CallInst *Create(Context& c, Function *func, std::vector<Value *> funcArgs,
                          BasicBlock *insertedBlock, std::string name = "v");

private:
};
