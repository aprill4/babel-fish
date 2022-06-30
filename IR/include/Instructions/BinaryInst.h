#pragma once
#include "Instruction.h"

class BinaryInst : public Instruction {
public:
  BinaryInst(Context &c, Type *type, InstId instId, Value *leftValue, Value *rightValue,
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
  static BinaryInst *CreateAnd(Context &context, Value *leftValue,
                                Value *rightValue, BasicBlock *insertedBlock);
  static BinaryInst *CreateOr(Context &context, Value *leftValue,
                                Value *rightValue, BasicBlock *insertedBlock);
private:
};