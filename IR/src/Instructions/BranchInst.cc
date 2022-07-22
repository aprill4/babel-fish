#include "Instructions/BranchInst.h"
#include "BasicBlock.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"

BranchInst::BranchInst(Context &context, BasicBlock *ifTrueBlock,
                       BasicBlock *insertedBlock)
    : Instruction(Type::getVoidType(context), InstId::Br, 1, insertedBlock) {
  setOperand(ifTrueBlock, 0);
  insertedBlock->addInstruction(this);
}

BranchInst::BranchInst(Context &context, Value *cond, BasicBlock *ifTrueBlock,
                       BasicBlock *ifFalseBlock, BasicBlock *insertedBlock)
    : Instruction(Type::getVoidType(context), InstId::Br, 3, insertedBlock) {
  setOperand(cond, 0);
  setOperand(ifTrueBlock, 1);
  setOperand(ifFalseBlock, 2);
  insertedBlock->addInstruction(this);
}

BranchInst *BranchInst::Create(Context &context, BasicBlock *ifTrueBlock,
                               BasicBlock *insertedBlock) {
  return new BranchInst(context, ifTrueBlock, insertedBlock);
}

BranchInst *BranchInst::Create(Context &context, Value *cond,
                               BasicBlock *ifTrueBlock,
                               BasicBlock *ifFalseBlock,
                               BasicBlock *insertedBlock) {
  return new BranchInst(context, cond, ifTrueBlock, ifFalseBlock,
                        insertedBlock);
}

bool BranchInst::isCondBr() { return getOperandNum() == 3; }

std::string BranchInst::print() {
  std::string IR;
  char IRtemp[100];
  if (isCondBr()) {
    // br i1 <cond>, label <iftrue>, label <iffalse>
    std::string fmt("br i1 %s, label %s, label %s");
    std::snprintf(
        IRtemp, sizeof IRtemp, fmt.c_str(), print_as_op(getOperand(0)).c_str(),
        print_as_op(getOperand(1)).c_str(), print_as_op(getOperand(2)).c_str());
  } else {
    // br label <dest>
    std::string fmt("br label %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(),
                  print_as_op(getOperand(0)).c_str());
  }
  IR.assign(IRtemp);
  return IR;
}
