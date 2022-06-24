#pragma once

#include "Instruction.h"

class ZextInst : public Instruction {
public:
  ZextInst(OpId op, Value *val, Type *ty, BasicBlock *bb);
  //   static ZextInst *create_zext(Value *val, Type *ty, BasicBlock *bb);
  //   Type *get_dest_type() const;
  std::string print() override;

private:
  Type *dest_ty_;
};
