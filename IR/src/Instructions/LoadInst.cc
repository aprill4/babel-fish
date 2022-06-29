#include "Instructions/LoadInst.h"
#include "BasicBlock.h"
#include "Types/PointerType.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"
#include <cassert>

LoadInst::LoadInst(Type *type, Value *ptr, BasicBlock *insertedBlock)
    : Instruction(type, InstId::Load, 1, insertedBlock) {
  setOperand(ptr, 0);
  insertedBlock->addInstruction(this);
}

LoadInst *LoadInst::Create(Type *type, Value *ptr, BasicBlock *insertedBlock) {
  return new LoadInst(type, ptr, insertedBlock);
}

std::string LoadInst::print() {
  std::string IR;
  char IRtemp[30];
  // <result> = load <type>, <type>* <pointer>
  std::string fmt("%%%s = load %s, %s %s");
  assert(getOperandType(0)->isPointerType());
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getName().c_str(),
                getOperandType(0)->getPtrElementType()->getTypeName().c_str(),
                getOperandTypeName(0).c_str(),
                print_as_op(getOperand(0)).c_str());
  IR.assign(IRtemp);
  return IR;
}