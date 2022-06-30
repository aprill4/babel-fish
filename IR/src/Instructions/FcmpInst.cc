#include "Instructions/FcmpInst.h"
#include "BasicBlock.h"
#include "Types/IntegerType.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"

FcmpInst::FcmpInst(Context &c, Type *type, FcmpOp fcmpOp, Value *leftValue,
                   Value *rightValue, BasicBlock *insertedBlock, std::string name)
    : Instruction(c, type, InstId::Fcmp, 2, insertedBlock, name), fcmpOp_(fcmpOp) {
  setOperand(leftValue, 0);
  setOperand(rightValue, 1);
  insertedBlock->addInstruction(this);
}

FcmpInst *FcmpInst::Create(Context &context, FcmpOp fcmpOp, Value *leftValue,
                           Value *rightValue, BasicBlock *insertedBlock, std::string name) {
  return new FcmpInst(context, Type::getInt1Type(context), fcmpOp, leftValue, rightValue,
                      insertedBlock, name);
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
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                  getFcmpOpName().c_str(), getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str(),
                  print_as_op(getOperand(1)).c_str());
  } else {
    std::string fmt("%%%s = fcmp %s %s %s, %s %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                  getFcmpOpName().c_str(), getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str(),
                  getOperandTypeName(1).c_str(),
                  print_as_op(getOperand(1)).c_str());
  }
  IR.assign(IRtemp);
  return IR;
}