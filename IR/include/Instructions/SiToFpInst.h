#pragma once

#include "Instruction.h"

class SiToFpInst : public Instruction {
public:
  SiToFpInst(OpId op, Value *val, Type *ty, BasicBlock *bb);
  //   static SiToFpInst *create_sitofp(Value *val, Type *ty, BasicBlock *bb);
  //   Type *get_dest_type() const;
  std::string print() override;

private:
  Type *destType_;
};