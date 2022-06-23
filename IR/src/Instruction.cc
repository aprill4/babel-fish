#include "../include/Instruction.h"

Instruction::Instruction(Type *type, OpId opId, std::size_t operandNum,
                         BasicBlock *parent, const std::string &name)
    : User(type, name, operandNum), opId_(opId), parent_(parent) {}

bool Instruction::isVoid() {
  //   return ((opId_ == ret) || (opId_ == br) || (opId_ == store) ||
  //   (opId_ == call && this->get_type()->is_void_type()));
  return false;
}

bool Instruction::isPhi() { return opId_ == OpId::phi; }
bool Instruction::isStore() { return opId_ == OpId::store; }
bool Instruction::isAlloca() { return opId_ == OpId::alloca; }
bool Instruction::isRet() { return opId_ == OpId::ret; }
bool Instruction::isLoad() { return opId_ == OpId::load; }
bool Instruction::isBr() { return opId_ == OpId::br; }

bool Instruction::isAdd() { return opId_ == OpId::add; }
bool Instruction::isSub() { return opId_ == OpId::sub; }
bool Instruction::isMul() { return opId_ == OpId::mul; }
bool Instruction::isDiv() { return opId_ == OpId::sdiv; }

bool Instruction::isFadd() { return opId_ == OpId::fadd; }
bool Instruction::isFsub() { return opId_ == OpId::fsub; }
bool Instruction::isFmul() { return opId_ == OpId::fmul; }
bool Instruction::isFdiv() { return opId_ == OpId::fdiv; }
bool Instruction::isFp2si() { return opId_ == OpId::fptosi; }
bool Instruction::isSi2fp() { return opId_ == OpId::sitofp; }

bool Instruction::isCmp() { return opId_ == OpId::cmp; }
bool Instruction::isFcmp() { return opId_ == OpId::fcmp; }

bool Instruction::isCall() { return opId_ == OpId::call; }
bool Instruction::isGep() { return opId_ == OpId::getelementptr; }
bool Instruction::isZext() { return opId_ == OpId::zext; }

bool Instruction::isBinary() {
  return (isAdd() || isSub() || isMul() || isDiv() || isFadd() || isFsub() ||
          isFmul() || isFdiv()) &&
         (getOperandNum() == 2);
}

bool Instruction::isTerminator() { return isBr() || isRet(); }