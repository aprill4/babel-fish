#include "Instructions/Instruction.h"
#include "BasicBlock.h"

Instruction::Instruction(Type *type, OpId opId, std::size_t operandNum,
                         BasicBlock *parent, const std::string &name)
    : User(type, name, operandNum), opId_(opId), parent_(parent) {}

Module *Instruction::getModule() { return parent_->getModule(); }

bool Instruction::isVoid() {
  return ((opId_ == OpId::ret) || (opId_ == OpId::br) ||
          (opId_ == OpId::store) ||
          (opId_ == OpId::call && getType()->isVoidType()));
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

bool Instruction::isIcmp() { return opId_ == OpId::icmp; }
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

std::string Instruction::getInstructionOpName() {
  std::string opName;
  switch (opId_) {
  case OpId::ret:
    opName = "ret";
    break;
  case OpId::br:
    opName = "br";
    break;
  case OpId::add:
    opName = "add";
    break;
  case OpId::sub:
    opName = "sub";
    break;
  case OpId::mul:
    opName = "mul";
    break;
  case OpId::sdiv:
    opName = "sdiv";
    break;
  case OpId::fadd:
    opName = "fadd";
    break;
  case OpId::fsub:
    opName = "fsub";
    break;
  case OpId::fmul:
    opName = "fmul";
    break;
  case OpId::fdiv:
    opName = "fdiv";
    break;
  case OpId::alloca:
    opName = "alloca";
    break;
  case OpId::load:
    opName = "load";
    break;
  case OpId::store:
    opName = "store";
    break;
  case OpId::icmp:
    opName = "cmp";
    break;
  case OpId::fcmp:
    opName = "fcmp";
    break;
  case OpId::phi:
    opName = "phi";
    break;
  case OpId::call:
    opName = "call";
    break;
  case OpId::getelementptr:
    opName = "getelementptr";
    break;
  case OpId::zext:
    opName = "zext";
    break;
  case OpId::fptosi:
    opName = "fptosi";
    break;
  case OpId::sitofp:
    opName = "sitofp";
    break;
  default:
    break;
  }
  return opName;
}