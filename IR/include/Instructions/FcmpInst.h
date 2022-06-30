#pragma once

#include "Instruction.h"

class FcmpInst : public Instruction {
public:
  enum FcmpOp { EQ, NEQ, GT, GTE, LT, LTE };
  FcmpInst(Context &c, Type *type, FcmpOp fcmpOp, Value *leftValue, Value *rightValue,
           BasicBlock *insertedBlock, std::string name);
  FcmpOp getFcmpOp();
  std::string getFcmpOpName();
  std::string print() override;

public:
  static FcmpInst *Create(Context &context, FcmpOp fcmpOp, Value *leftValue,
                          Value *rightValue, BasicBlock *insertedBlock, std::string name = "v");

private:
  FcmpOp fcmpOp_;
};
