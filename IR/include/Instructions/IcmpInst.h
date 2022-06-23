#pragma once

#include "Instruction.h"

class Module;
class Value;

class IcmpInst : public Instruction {
public:
  enum class IcmpOp { EQ, NEQ, GT, GTE, LT, LTE };
  IcmpInst(Type *type, Value *lhs, IcmpOp icmpOp, Value *rhs, BasicBlock *bb);
  IcmpOp getIcmpOp();
  // static IcmpInst *create_icmp(Module *module, IcmpOp icmpOp, Value *lhs,
  //                              Value *rhs, BasicBlock *bb);
  std::string print() override;
  std::string getIcmpOpName();

private:
  IcmpOp icmpOp_;
};