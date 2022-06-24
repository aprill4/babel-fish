#pragma once
#include "Instruction.h"

class StoreInst : public Instruction {

public:
  StoreInst(Value *val, Value *ptr, BasicBlock *bb);

  //   Value *get_rval() { return this->get_operand(0); }
  //   Value *get_lval() { return this->get_operand(1); }
  std::string print() override;
};