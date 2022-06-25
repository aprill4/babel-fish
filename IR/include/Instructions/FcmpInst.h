#pragma once

#include "Instruction.h"

class FcmpInst : public Instruction {
public:
  enum FcmpOp { EQ, NEQ, GT, GTE, LT, LTE };
  FcmpInst(Type *type, FcmpOp fcmpOp, Value *leftValue, Value *rightValue,
           BasicBlock *insertedBlock);
  FcmpOp getFcmpOp();
  std::string getFcmpOpName();
  std::string print() override;

public:
  static FcmpInst *Create(Context &context, FcmpOp fcmpOp, Value *leftValue,
                          Value *rightValue, BasicBlock *insertedBlock);

private:
  FcmpOp fcmpOp_;
};
