#include "Instructions/ReturnInst.h"
#include "BasicBlock.h"
#include "Module.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"
#include <cassert>
#include <iostream>

ReturnInst::ReturnInst(Context &context, BasicBlock *insertedBlock)
    : Instruction(Type::getVoidType(context), InstId::Ret, 0, insertedBlock) {
  assert(insertedBlock != nullptr);
  insertedBlock->addInstruction(this);
}

ReturnInst::ReturnInst(Context &context, Value *value,
                       BasicBlock *insertedBlock)
    : Instruction(Type::getVoidType(context), InstId::Ret, 1, insertedBlock) {
  assert(insertedBlock != nullptr);
  insertedBlock->addInstruction(this);
  setOperand(value, 0);
}

ReturnInst *ReturnInst::Create(Context &context, BasicBlock *insertedBlock) {
  assert(insertedBlock != nullptr);
  return new ReturnInst(context, insertedBlock);
}

ReturnInst *ReturnInst::Create(Context &context, Value *retVal,
                               BasicBlock *insertedBlock) {
  assert(insertedBlock != nullptr);
  return new ReturnInst(context, retVal, insertedBlock);
}

bool ReturnInst::isRetVoid() { return getOperandNum() == 0; }

std::string ReturnInst::print() {
  std::string IR;
  char IRtemp[30];
  if (!isRetVoid()) {
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
