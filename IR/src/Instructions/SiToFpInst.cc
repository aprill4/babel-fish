#include "Instructions/SiToFpInst.h"
#include "BasicBlock.h"
#include "Util.h"

SiToFpInst::SiToFpInst(Context &c, Type *destType, Value *value, BasicBlock *insertedBlock, std::string name)
    : Instruction(c, destType, InstId::Sitofp, 1, insertedBlock, name),
      destType_(destType) {
  setOperand(value, 0);
  insertedBlock->addInstruction(this);
}

SiToFpInst *SiToFpInst::Create(Context &c, Type *destType, Value *value,
                               BasicBlock *insertedBlock, std::string name) {
  return new SiToFpInst(c, destType, value, insertedBlock, name);
}

Type *SiToFpInst::getDestType() { return destType_; }

std::string SiToFpInst::print() {
  std::string IR;
  char IRtemp[100];
  // <result> = sitofp <type> <value> to <type2>
  std::string fmt("%%%s = sitofp %s %s to %s");
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                getOperandType(0)->getTypeName().c_str(),
                print_as_op(getOperand(0)).c_str(),
                destType_->getTypeName().c_str());
  IR.assign(IRtemp);
  return IR;
}