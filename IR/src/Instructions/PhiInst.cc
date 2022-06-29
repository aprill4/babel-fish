#include "Instructions/PhiInst.h"
#include "BasicBlock.h"
#include "Util.h"

PhiInst::PhiInst(Type *type,
                 std::vector<std::pair<Value *, BasicBlock *>> valAndLabels,
                 BasicBlock *insertedBlock)
    : Instruction(type, InstId::Phi, 2 * valAndLabels.size(), insertedBlock) {
  for (int i = 0; i < valAndLabels.size(); i++) {
    setOperand(valAndLabels[i].first, 2 * i);
    setOperand(valAndLabels[i].second, 2 * i + 1);
  }
  insertedBlock->addInstruction(this);
}

PhiInst *
PhiInst::Create(Type *type,
                std::vector<std::pair<Value *, BasicBlock *>> valAndLabels,
                BasicBlock *insertedBlock) {
  return new PhiInst(type, valAndLabels, insertedBlock);
}

std::string PhiInst::print() {
  std::string IR;
  char IRtemp[30];
  // <result> = phi <ty> [ <val0>, <label0>], ...
  std::string fmt("%%%s = phi %s ");
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getName().c_str(),
                getOperandType(0)->getTypeName().c_str());
  IR.assign(IRtemp);
  for (int i = 0; i < getOperandNum() / 2; i++) {
    if (i > 0)
      IR += ", ";
    IR += "[ ";
    IR += print_as_op(getOperand(2 * i));
    IR += ", ";
    IR += print_as_op(getOperand(2 * i + 1));
    IR += " ]";
  }
  return IR;
}