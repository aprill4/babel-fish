#include "Instructions/FpToSiInst.h"
#include "BasicBlock.h"
#include "Util.h"

FpToSiInst::FpToSiInst(Context &c, Type *destType, Value *value, BasicBlock *insertedBlock, std::string name)
    : Instruction(c, destType, InstId::Fptosi, 1, insertedBlock, name),
      destType_(destType) {
  setOperand(value, 0);
  insertedBlock->addInstruction(this);
}

FpToSiInst *FpToSiInst::Create(Context &c, Type *destType, Value *value,
                               BasicBlock *insertedBlock, std::string name) {
  return new FpToSiInst(c, destType, value, insertedBlock, name);
}

Type *FpToSiInst::getDestType() { return destType_; }

std::string FpToSiInst::print() {
  std::string IR;
  char IRtemp[30];
  // <result> = fptosi <type> <value> to <type2>
  std::string fmt("%%%s = fptosi %s %s to %s");
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                getOperandType(0)->getTypeName().c_str(),
                print_as_op(getOperand(0)).c_str(),
                destType_->getTypeName().c_str());
  IR.assign(IRtemp);
  return IR;
}