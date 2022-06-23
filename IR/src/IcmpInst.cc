#include "../include/IcmpInst.h"
#include "../include/BasicBlock.h"
#include "../include/Value.h"
#include "../include/Type.h"


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

std::string IcmpInst::print() {
  std::string IR;
  IR += "%";
  IR += getName();
  IR += " = ";
  IR += getInstructionOpName();
  IR += " ";
  IR += getIcmpOpName();
  IR += " ";
  IR += getOperand(0)->getType()->getTypeName();
//   IR += " ";
//   IR += print_as_op(this->get_operand(0), false);
//   IR += ", ";
//   if (Type::is_eq_type(this->get_operand(0)->get_type(),
//                        this->get_operand(1)->get_type())) {
//     IR += print_as_op(this->get_operand(1), false);
//   } else {
//     IR += print_as_op(this->get_operand(1), true);
//   }
  return IR;
}