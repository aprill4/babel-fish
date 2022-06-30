#pragma once

#include "Instruction.h"

class GetElementPtrInst : public Instruction {
public:
  GetElementPtrInst(Context &context, Value *ptr, std::vector<Value *> idxList,
                    BasicBlock *insertedBlock, std::string name);
  Type *getElementType();
  Type *computeElementType(Value *ptr, std::vector<Value *> idxList);
  std::string print() override;

public:
  static GetElementPtrInst *Create(Context &context, Value *ptr,
                                   std::vector<Value *> idxList,
                                   BasicBlock *insertedBlock, std::string name = "ptr_");

private:
  Type *elementType_;
};