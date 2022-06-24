#include "Instructions/BinaryInst.h"
#include "BasicBlock.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"


BinaryInst::BinaryInst(Type *type, OpId opId, Value *valueL, Value *valueR,
                       BasicBlock *bb)
    : Instruction(type, opId, 2, bb) {
  setOperand(valueL, 0);
  setOperand(valueR, 1);
}

std::string BinaryInst::print() {
  std::string IR;
  char IRtemp[30];
  if (Type::isEqType(getOperandType(0), getOperandType(1))) {
    // <result> = add <type> <op1>, <op2>
    std::string fmt("%%%s = %s %s %s, %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getName().c_str(),
                  getInstructionOpName().c_str(), getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str(),
                  print_as_op(getOperand(1)).c_str());
  } else {
    // <result> = add <type> <op1>, <type> <op2>
    std::string fmt("%%%s = %s %s %s, %s %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getName().c_str(),
                  getInstructionOpName().c_str(), getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str(),
                  getOperandTypeName(1).c_str(),
                  print_as_op(getOperand(1)).c_str());
  }
  IR.assign(IRtemp);
  return IR;
}