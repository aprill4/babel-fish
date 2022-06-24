#pragma once

#include "Instruction.h"

class FunctionType;
class Function;

class CallInst : public Instruction {
public:
  CallInst(Function *func, std::vector<Value *> args, BasicBlock *bb);
  FunctionType *getFunctionType();
  std::string print() override; 
private:
};
