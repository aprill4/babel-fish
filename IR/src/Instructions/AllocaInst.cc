#include "Instructions/AllocaInst.h"
#include "BasicBlock.h"
#include "Types/PointerType.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"

AllocaInst::AllocaInst(Context &context, Type *allocaType,
                       BasicBlock *insertedBlock, std::string name)
    : Instruction(context, PointerType::get(context, allocaType), InstId::Alloca, 0,
                  insertedBlock, name),
      allocaType_(allocaType) {
  insertedBlock->addInstruction(this);
}

AllocaInst *AllocaInst::Create(Context &context, Type *allocaType,
                               BasicBlock *insertedBlock, std::string name) {
  return new AllocaInst(context, allocaType, insertedBlock, name);
}

Type *AllocaInst::getAllocaType() { return allocaType_; }

std::string AllocaInst::print() {
  std::string IR;
  char IRtemp[100];
  // <result> = alloca <type>
  std::string fmt("%%%s = alloca %s");
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                allocaType_->getTypeName().c_str());
  IR.assign(IRtemp);
  return IR;
}
