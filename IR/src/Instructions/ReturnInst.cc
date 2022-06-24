#include "Instructions/ReturnInst.h"
#include "BasicBlock.h"
#include "Module.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"
#include <iostream>

ReturnInst::ReturnInst(Value *value, BasicBlock *bb)
    : Instruction(bb->getModule()->getVoidType(), OpId::ret, 1, bb) {
  setOperand(value, 0);
}

ReturnInst::ReturnInst(BasicBlock *bb)
    : Instruction(bb->getModule()->getVoidType(), OpId::ret, 0, bb) {}

bool ReturnInst::isVoidRet() { return getOperandNum() == 0; }

std::string ReturnInst::print() {
  std::string IR;
  char IRtemp[30];
  if (!isVoidRet()) {
    // ret <type> <value>
    std::string fmt("ret %s %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(),
                  getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str());
  } else {
    // ret void
    return std::string("ret void");
  }
  IR.assign(IRtemp);
  return IR;
}
