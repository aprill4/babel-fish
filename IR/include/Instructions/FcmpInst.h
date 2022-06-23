#pragma once

#include "Instruction.h"

class FcmpInst : public Instruction {
public:
  enum FcmpOp { EQ, NEQ, GT, GTE, LT, LTE };
  FcmpInst(Type *type, FcmpOp fcmpOp, Value *lhs, Value *rhs, BasicBlock *bb);

public:
  //   static FCmpInst *create_fcmp(CmpOp op, Value *lhs, Value *rhs, BasicBlock
  //   *bb,
  //    Module *m);

  FcmpOp getFcmpOp();

  virtual std::string print() override;
  std::string getFcmpOpName();

private:
  FcmpOp fcmpOp_;
};
