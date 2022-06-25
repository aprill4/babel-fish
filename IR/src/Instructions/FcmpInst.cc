#include "Instructions/FcmpInst.h"
#include "BasicBlock.h"
#include "Types/IntegerType.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"

FcmpInst::FcmpInst(Type *type, FcmpOp fcmpOp, Value *leftValue,
                   Value *rightValue, BasicBlock *insertedBlock)
    : Instruction(type, InstId::fcmp, 2, insertedBlock), fcmpOp_(fcmpOp) {
  setOperand(leftValue, 0);
  setOperand(rightValue, 1);
  insertedBlock->addInstruction(this);
}

FcmpInst *FcmpInst::Create(Context &context, FcmpOp fcmpOp, Value *leftValue,
                           Value *rightValue, BasicBlock *insertedBlock) {
  return new FcmpInst(Type::getInt1Type(context), fcmpOp, leftValue, rightValue,
                      insertedBlock);
}

FcmpInst::FcmpOp FcmpInst::getFcmpOp() { return fcmpOp_; }

std::string FcmpInst::getFcmpOpName() {
  std::string icmpOpName;
  switch (fcmpOp_) {
  case FcmpOp::EQ:
    icmpOpName = "ueq";
    break;
  case FcmpOp::NEQ:
    icmpOpName = "une";
    break;
  case FcmpOp::GT:
    icmpOpName = "ugt";
    break;
  case FcmpOp::GTE:
    icmpOpName = "uge";
    break;
  case FcmpOp::LT:
    icmpOpName = "ult";
    break;
  case FcmpOp::LTE:
    icmpOpName = "ule";
    break;
  default:
    icmpOpName = "fcmpOp error";
    break;
  }
  return icmpOpName;
}

std::string FcmpInst::print() {
  std::string IR;
  char IRtemp[30];
  if (getOperandType(0) == getOperandType(1)) {
    std::string fmt("%%%s = fcmp %s %s %s, %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getName().c_str(),
                  getFcmpOpName().c_str(), getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str(),
                  print_as_op(getOperand(1)).c_str());
  } else {
    std::string fmt("%%%s = fcmp %s %s %s, %s %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getName().c_str(),
                  getFcmpOpName().c_str(), getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str(),
                  getOperandTypeName(1).c_str(),
                  print_as_op(getOperand(1)).c_str());
  }
  IR.assign(IRtemp);
  return IR;
}