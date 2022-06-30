#include "Instructions/BinaryInst.h"
#include "BasicBlock.h"
#include "Types/IntegerType.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"

BinaryInst::BinaryInst(Context &c, Type *type, InstId instId, Value *leftValue,
                       Value *rightValue, BasicBlock *insertedBlock)
    : Instruction(c, type, instId, 2, insertedBlock) {
  setOperand(leftValue, 0);
  setOperand(rightValue, 1);
  insertedBlock->addInstruction(this);
}

BinaryInst *BinaryInst::CreateAdd(Context &context, Value *leftValue,
                                  Value *rightValue,
                                  BasicBlock *insertedBlock) {
  return new BinaryInst(context, Type::getInt32Type(context), InstId::Add, leftValue,
                        rightValue, insertedBlock);
}

BinaryInst *BinaryInst::CreateSub(Context &context, Value *leftValue,
                                  Value *rightValue,
                                  BasicBlock *insertedBlock) {
  return new BinaryInst(context, Type::getInt32Type(context), InstId::Sub, leftValue,
                        rightValue, insertedBlock);
}

BinaryInst *BinaryInst::CreateMul(Context &context, Value *leftValue,
                                  Value *rightValue,
                                  BasicBlock *insertedBlock) {
  return new BinaryInst(context, Type::getInt32Type(context), InstId::Mul, leftValue,
                        rightValue, insertedBlock);
}

BinaryInst *BinaryInst::CreateSdiv(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock) {
  return new BinaryInst(context, Type::getInt32Type(context), InstId::Sdiv, leftValue,
                        rightValue, insertedBlock);
}

BinaryInst *BinaryInst::CreateFadd(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock) {
  return new BinaryInst(context, Type::getFloatType(context), InstId::Fadd, leftValue,
                        rightValue, insertedBlock);
}

BinaryInst *BinaryInst::CreateFsub(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock) {
  return new BinaryInst(context, Type::getFloatType(context), InstId::Fsub, leftValue,
                        rightValue, insertedBlock);
}

BinaryInst *BinaryInst::CreateFmul(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock) {
  return new BinaryInst(context, Type::getFloatType(context), InstId::Fmul, leftValue,
                        rightValue, insertedBlock);
}

BinaryInst *BinaryInst::CreateFdiv(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock) {
  return new BinaryInst(context, Type::getFloatType(context), InstId::Fdiv, leftValue,
                        rightValue, insertedBlock);
}

BinaryInst *BinaryInst::CreateAnd(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock) {
  return new BinaryInst(context, Type::getFloatType(context), InstId::And, leftValue,
                        rightValue, insertedBlock);
}

BinaryInst *BinaryInst::CreateOr(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock) {
  return new BinaryInst(context, Type::getFloatType(context), InstId::Or, leftValue,
                        rightValue, insertedBlock);
}

std::string BinaryInst::print() {
  std::string IR;
  char IRtemp[30];
  if (getOperandType(0) == getOperandType(1)) {
    // <result> = add <type> <op1>, <op2>
    std::string fmt("%%%s = %s nsw %s %s, %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getName().c_str(),
                  getInstructionOpName().c_str(), getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str(),
                  print_as_op(getOperand(1)).c_str());
  } else {
    // <result> = add <type> <op1>, <type> <op2>
    std::string fmt("%%%s = %s nsw %s %s, %s %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getName().c_str(),
                  getInstructionOpName().c_str(), getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str(),
                  getOperandTypeName(1).c_str(),
                  print_as_op(getOperand(1)).c_str());
  }
  IR.assign(IRtemp);
  return IR;
}