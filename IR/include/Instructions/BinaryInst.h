#pragma once
#include "Instruction.h"

class BinaryInst : public Instruction {
public:
  BinaryInst(Type *type, InstId instId, Value *leftValue, Value *rightValue,
             BasicBlock *insertedBlock);
  std::string print() override;

public:
  static BinaryInst *CreateAdd(Context &context, Value *leftValue,
                               Value *rightValue, BasicBlock *insertedBlock);
  static BinaryInst *CreateSub(Context &context, Value *leftValue,
                               Value *rightValue, BasicBlock *insertedBlock);
  static BinaryInst *CreateMul(Context &context, Value *leftValue,
                               Value *rightValue, BasicBlock *insertedBlock);
  static BinaryInst *CreateSdiv(Context &context, Value *leftValue,
                                Value *rightValue, BasicBlock *insertedBlock);
  static BinaryInst *CreateFadd(Context &context, Value *leftValue,
                                Value *rightValue, BasicBlock *insertedBlock);
  static BinaryInst *CreateFsub(Context &context, Value *leftValue,
                                Value *rightValue, BasicBlock *insertedBlock);
  static BinaryInst *CreateFmul(Context &context, Value *leftValue,
                                Value *rightValue, BasicBlock *insertedBlock);
  static BinaryInst *CreateFdiv(Context &context, Value *leftValue,
                                Value *rightValue, BasicBlock *insertedBlock);

private:
};