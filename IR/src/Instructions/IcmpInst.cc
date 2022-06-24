#include "Instructions/IcmpInst.h"
#include "BasicBlock.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"
#include <string>

IcmpInst::IcmpInst(Type *type, Value *lhs, IcmpOp icmpOp, Value *rhs,
                   BasicBlock *bb)
    : Instruction(type, Instruction::OpId::icmp, 2, bb), icmpOp_(icmpOp) {}

std::string IcmpInst::getIcmpOpName() {
  std::string icmpOpName;
  switch (icmpOp_) {
  case IcmpOp::EQ:
    icmpOpName = "eq";
    break;
  case IcmpOp::NEQ:
    icmpOpName = "neq";
    break;
  case IcmpOp::GT:
    icmpOpName = "sgt";
    break;
  case IcmpOp::GTE:
    icmpOpName = "sge";
    break;
  case IcmpOp::LT:
    icmpOpName = "slt";
    break;
  case IcmpOp::LTE:
    icmpOpName = "sle";
    break;
  default:
    icmpOpName = "icmpOp error";
    break;
  }
  return icmpOpName;
}

IcmpInst::IcmpOp IcmpInst::getIcmpOp() { return icmpOp_; }

std::string IcmpInst::print() {
  std::string IR;
  char IRtemp[30];
  if (Type::isEqType(getOperandType(0), getOperandType(1))) {
    // <result> = icmp <cond> <type> <op1>, <op2>
    std::string fmt("%%%s = icmp %s %s %s, %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getName().c_str(),
                  getIcmpOpName().c_str(), getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str(),
                  print_as_op(getOperand(1)).c_str());
  } else {
    // <result> = icmp <cond> <type> <op1>, <type> <op2>
    std::string fmt("%%%s = icmp %s %s %s, %s %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getName().c_str(),
                  getIcmpOpName().c_str(), getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str(),
                  getOperandTypeName(1).c_str(),
                  print_as_op(getOperand(1)).c_str());
  }
  IR.assign(IRtemp);
  return IR;
}