#pragma once

#include "Instruction.h"

class Module;
class Value;

class IcmpInst : public Instruction {
public:
  enum class IcmpOp { EQ, NEQ, GT, GTE, LT, LTE };
  IcmpInst(Context &c, Type *type, IcmpOp icmpOp, Value *leftValue, Value *rightValue,
           BasicBlock *insertedBlock, std::string name);
  IcmpOp getIcmpOp();
  std::string getIcmpOpName();
  std::string print() override;

public:
  static IcmpInst *Create(Context &context, IcmpOp icmpOp, Value *leftValue,
                          Value *rightValue, BasicBlock *insertedBlock, std::string name = "bool_");

private:
  IcmpOp icmpOp_;
};