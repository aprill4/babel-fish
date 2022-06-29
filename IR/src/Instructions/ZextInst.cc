#include "Instructions/ZextInst.h"
#include "BasicBlock.h"
#include "Util.h"

ZextInst::ZextInst(Type *destType, Value *value, BasicBlock *insertedBlock)
    : Instruction(destType, InstId::Zext, 1, insertedBlock),
      destType_(destType) {
  setOperand(value, 0);
  insertedBlock->addInstruction(this);
}

ZextInst *ZextInst::Create(Type *destType, Value *value,
                           BasicBlock *insertedBlock) {
  return new ZextInst(destType, value, insertedBlock);
}

Type *ZextInst::getDestType() { return destType_; }

std::string ZextInst::print() {
  std::string IR;
  char IRtemp[30];
  // <result> = zext <type> <value> to <type2>
  std::string fmt("%%%s = zext %s %s to %s");
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getName().c_str(),
                getOperandType(0)->getTypeName().c_str(),
                print_as_op(getOperand(0)).c_str(),
                destType_->getTypeName().c_str());
  IR.assign(IRtemp);
  return IR;
}