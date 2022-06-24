#pragma once

#include "Instruction.h"

class GetElementPtrInst : public Instruction {
public:
  GetElementPtrInst(Value *ptr, std::vector<Value *> idxs, BasicBlock *bb);
  //   static Type *get_element_type(Value *ptr, std::vector<Value *> idxs);
  //   static GetElementPtrInst *create_gep(Value *ptr, std::vector<Value *>
  //   idxs,
  //    BasicBlock *bb);
  Type *getElementType();
  std::string print() override;

private:
  Type *elementType_;
};