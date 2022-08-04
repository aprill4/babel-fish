#include "UnaryInst.h"
#include "BasicBlock.h"
#include "Util.h"

UnaryInst::UnaryInst(Context &c, Type *type, InstId instId, Value *rightValue,
                     BasicBlock *insertedBlock, std::string name)
    : Instruction(c, type, instId, 1, insertedBlock, name) {
  setOperand(rightValue, 0);
  insertedBlock->addInstruction(this);
}

UnaryInst *UnaryInst::CreateNegative(Context &context, Value *rightValue,
                                     BasicBlock *insertedBlock,
                                     std::string name) {
  return new UnaryInst(context, rightValue->getType(), InstId::Negative,
                       rightValue, insertedBlock, name);
}
UnaryInst *UnaryInst::CreateNot(Context &context, Value *rightValue,
                                BasicBlock *insertedBlock, std::string name) {
  return new UnaryInst(context, Type::getInt1Type(context), InstId::Not,
                       rightValue, insertedBlock, name);
}

std::string UnaryInst::print() {
  std::string IR;
  char IRtemp[256];
  // <result> = <not/negative> <type> <op1>
  std::string fmt("%%%s = %s %s %s");
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                getInstructionOpName().c_str(), getOperandTypeName(0).c_str(),
                print_as_op(getOperand(0)).c_str());
  IR.assign(IRtemp);
  return IR;
}
