#include "Instructions/SiToFpInst.h"
#include "BasicBlock.h"
#include "Util.h"

SiToFpInst::SiToFpInst(Context &c, Type *destType, Value *value, BasicBlock *insertedBlock)
    : Instruction(c, destType, InstId::Sitofp, 1, insertedBlock),
      destType_(destType) {
  setOperand(value, 0);
  insertedBlock->addInstruction(this);
}

SiToFpInst *SiToFpInst::Create(Context &c, Type *destType, Value *value,
                               BasicBlock *insertedBlock) {
  return new SiToFpInst(c, destType, value, insertedBlock);
}

Type *SiToFpInst::getDestType() { return destType_; }

std::string SiToFpInst::print() {
  std::string IR;
  char IRtemp[30];
  // <result> = sitofp <type> <value> to <type2>
  std::string fmt("%%%s = sitofp %s %s to %s");
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getName().c_str(),
                getOperandType(0)->getTypeName().c_str(),
                print_as_op(getOperand(0)).c_str(),
                destType_->getTypeName().c_str());
  IR.assign(IRtemp);
  return IR;
}