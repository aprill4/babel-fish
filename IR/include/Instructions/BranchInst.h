#pragma once

#include "Instruction.h"

class BranchInst : public Instruction {
public:
  BranchInst(Context &context, BasicBlock *ifTrueBlock,
             BasicBlock *insertedBlock);
  BranchInst(Context &context, Value *cond, BasicBlock *ifTrueBlock,
             BasicBlock *ifFalseBlock, BasicBlock *insertedBlock);
  bool isCondBr();
  std::string print() override;

public:
  static BranchInst *Create(Context &context, BasicBlock *ifTrueBlock,
                            BasicBlock *insertedBlock);
  static BranchInst *Create(Context &context, Value *cond,
                            BasicBlock *ifTrueBlock, BasicBlock *ifFalseBlock,
                            BasicBlock *insertedBlock);

private:
};
