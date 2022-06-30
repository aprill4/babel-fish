#include "Instructions/LoadInst.h"
#include "BasicBlock.h"
#include "Types/PointerType.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"
#include <cassert>

LoadInst::LoadInst(Context &c, Type *type, Value *ptr, BasicBlock *insertedBlock, std::string name)
    : Instruction(c, type, InstId::Load, 1, insertedBlock, name) {
  setOperand(ptr, 0);
  insertedBlock->addInstruction(this);
}

LoadInst *LoadInst::Create(Context &c, Type *type, Value *ptr, BasicBlock *insertedBlock, std::string name) {
  return new LoadInst(c, type, ptr, insertedBlock, name);
}

std::string LoadInst::print() {
  std::string IR;
  char IRtemp[30];
  // <result> = load <type>, <type>* <pointer>
  std::string fmt("%%%s = load %s, %s %s");
  assert(getOperandType(0)->isPointerType());
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                getOperandType(0)->getPtrElementType()->getTypeName().c_str(),
                getOperandTypeName(0).c_str(),
                print_as_op(getOperand(0)).c_str());
  IR.assign(IRtemp);
  return IR;
}