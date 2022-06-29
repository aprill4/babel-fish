#include "Instructions/BinaryInst.h"
#include "BasicBlock.h"
#include "Types/IntegerType.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"

BinaryInst::BinaryInst(Type *type, InstId instId, Value *leftValue,
                       Value *rightValue, BasicBlock *insertedBlock)
    : Instruction(type, instId, 2, insertedBlock) {
  setOperand(leftValue, 0);
  setOperand(rightValue, 1);
  insertedBlock->addInstruction(this);
}

BinaryInst *BinaryInst::CreateAdd(Context &context, Value *leftValue,
                                  Value *rightValue,
                                  BasicBlock *insertedBlock) {
  return new BinaryInst(Type::getInt32Type(context), InstId::add, leftValue,
                        rightValue, insertedBlock);
}

BinaryInst *BinaryInst::CreateSub(Context &context, Value *leftValue,
                                  Value *rightValue,
                                  BasicBlock *insertedBlock) {
  return new BinaryInst(Type::getInt32Type(context), InstId::sub, leftValue,
                        rightValue, insertedBlock);
}

BinaryInst *BinaryInst::CreateMul(Context &context, Value *leftValue,
                                  Value *rightValue,
                                  BasicBlock *insertedBlock) {
  return new BinaryInst(Type::getInt32Type(context), InstId::mul, leftValue,
                        rightValue, insertedBlock);
}

BinaryInst *BinaryInst::CreateSdiv(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock) {
  return new BinaryInst(Type::getInt32Type(context), InstId::sdiv, leftValue,
                        rightValue, insertedBlock);
}

BinaryInst *BinaryInst::CreateFadd(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock) {
  return new BinaryInst(Type::getFloatType(context), InstId::fadd, leftValue,
                        rightValue, insertedBlock);
}

BinaryInst *BinaryInst::CreateFsub(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock) {
  return new BinaryInst(Type::getFloatType(context), InstId::fsub, leftValue,
                        rightValue, insertedBlock);
}

BinaryInst *BinaryInst::CreateFmul(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock) {
  return new BinaryInst(Type::getFloatType(context), InstId::fmul, leftValue,
                        rightValue, insertedBlock);
}

BinaryInst *BinaryInst::CreateFdiv(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock) {
  return new BinaryInst(Type::getFloatType(context), InstId::fdiv, leftValue,
                        rightValue, insertedBlock);
}

BinaryInst *BinaryInst::CreateAnd(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock) {
  return new BinaryInst(Type::getFloatType(context), InstId::and, leftValue,
                        rightValue, insertedBlock);
}

BinaryInst *BinaryInst::CreateOr(Context &context, Value *leftValue,
                                   Value *rightValue,
                                   BasicBlock *insertedBlock) {
  return new BinaryInst(Type::getFloatType(context), InstId::or, leftValue,
                        rightValue, insertedBlock);
}

std::string BinaryInst::print() {
  std::string IR;
  char IRtemp[30];
  if (getOperandType(0) == getOperandType(1)) {
    // <result> = add <type> <op1>, <op2>
    std::string fmt("%%%s = %s %s %s, %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getName().c_str(),
                  getInstructionOpName().c_str(), getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str(),
                  print_as_op(getOperand(1)).c_str());
  } else {
    // <result> = add <type> <op1>, <type> <op2>
    std::string fmt("%%%s = %s %s %s, %s %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getName().c_str(),
                  getInstructionOpName().c_str(), getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str(),
                  getOperandTypeName(1).c_str(),
                  print_as_op(getOperand(1)).c_str());
  }
  IR.assign(IRtemp);
  return IR;
}