#include "Instructions/StoreInst.h"
#include "BasicBlock.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"

StoreInst::StoreInst(Context &context, Value *value, Value *ptr,
                     BasicBlock *insertedBlock)
    : Instruction(Type::getVoidType(context), InstId::Store, 2, insertedBlock) {
  setOperand(value, 0);
  setOperand(ptr, 1);
  insertedBlock->addInstruction(this);
}

StoreInst *StoreInst::Create(Context &context, Value *value, Value *ptr,
                             BasicBlock *insertedBlock) {
  return new StoreInst(context, value, ptr, insertedBlock);
}

std::string StoreInst::print() {
  std::string IR;
  char IRtemp[30];
  // store <type> <value>, <type>* <pointer>
  std::string fmt("store %s %s, %s %s");
  std::snprintf(
      IRtemp, sizeof IRtemp, fmt.c_str(), getOperandTypeName(0).c_str(),
      print_as_op(getOperand(0)).c_str(), getOperandTypeName(1).c_str(),
      print_as_op(getOperand(1)).c_str());
  IR.assign(IRtemp);
  return IR;
}