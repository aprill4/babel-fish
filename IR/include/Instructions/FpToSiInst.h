#pragma once
#include "Instruction.h"

class FpToSiInst : public Instruction {
public:
  FpToSiInst(OpId op, Value *val, Type *ty, BasicBlock *bb);
  //   static FpToSiInst *create_fptosi(Value *val, Type *ty, BasicBlock *bb);
  //   Type *get_dest_type();
  std::string print() override;

private:
  Type *destType_;
};