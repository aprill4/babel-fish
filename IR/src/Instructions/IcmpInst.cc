#include "Instructions/IcmpInst.h"
#include "BasicBlock.h"
#include "Types/IntegerType.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"
#include <string>

IcmpInst::IcmpInst(Type *type, IcmpOp icmpOp, Value *leftValue,
                   Value *rightValue, BasicBlock *insertedBlock)
    : Instruction(type, InstId::icmp, 2, insertedBlock), icmpOp_(icmpOp) {
  setOperand(leftValue, 0);
  setOperand(rightValue, 0);
  insertedBlock->addInstruction(this);
}

IcmpInst *IcmpInst::Create(Context &context, IcmpOp icmpOp, Value *leftValue,
                           Value *rightValue, BasicBlock *insertedBlock) {
  return new IcmpInst(Type::getInt1Type(context), icmpOp, leftValue, rightValue,
                      insertedBlock);
}

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
  if (getOperandType(0) == getOperandType(1)) {
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