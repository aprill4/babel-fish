#include "Instructions/ZextInst.h"
#include "BasicBlock.h"
#include "Util.h"

ZextInst::ZextInst(Context &c, Type *destType, Value *value, BasicBlock *insertedBlock, std::string name)
    : Instruction(c, destType, InstId::Zext, 1, insertedBlock, name),
      destType_(destType) {
  setOperand(value, 0);
  insertedBlock->addInstruction(this);
}

ZextInst *ZextInst::Create(Context &c, Type *destType, Value *value,
                           BasicBlock *insertedBlock, std::string name) {
  return new ZextInst(c, destType, value, insertedBlock, name);
}

Type *ZextInst::getDestType() { return destType_; }

std::string ZextInst::print() {
  std::string IR;
  char IRtemp[100];
  // <result> = zext <type> <value> to <type2>
  std::string fmt("%%%s = zext %s %s to %s");
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                getOperandType(0)->getTypeName().c_str(),
                print_as_op(getOperand(0)).c_str(),
                destType_->getTypeName().c_str());
  IR.assign(IRtemp);
  return IR;
}