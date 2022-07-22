#include "Instructions/PhiInst.h"
#include "BasicBlock.h"
#include "Util.h"

PhiInst::PhiInst(Context &c, Type *type,
                 std::vector<std::pair<Value *, BasicBlock *>> valAndLabels,
                 BasicBlock *insertedBlock, std::string name)
    : Instruction(c, type, InstId::Phi, 2 * valAndLabels.size(), insertedBlock, name) {
  for (int i = 0; i < valAndLabels.size(); i++) {
    setOperand(valAndLabels[i].first, 2 * i);
    setOperand(valAndLabels[i].second, 2 * i + 1);
  }
  insertedBlock->addInstruction(this);
}

PhiInst *
PhiInst::Create(Context &c, Type *type,
                std::vector<std::pair<Value *, BasicBlock *>> valAndLabels,
                BasicBlock *insertedBlock, std::string name) {
  return new PhiInst(c, type, valAndLabels, insertedBlock, name);
}

std::string PhiInst::print() {
  std::string IR;
  char IRtemp[100];
  // <result> = phi <ty> [ <val0>, <label0>], ...
  std::string fmt("%%%s = phi %s ");
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
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