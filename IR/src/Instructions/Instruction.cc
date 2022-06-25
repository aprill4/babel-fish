#include "Instructions/Instruction.h"
#include "BasicBlock.h"

Instruction::Instruction(Type *type, InstId instId, std::size_t operandNum,
                         BasicBlock *parent)
    : User(type, "", operandNum), instId_(instId), parent_(parent) {}

Module *Instruction::getModule() { return parent_->getModule(); }

bool Instruction::isVoid() {
  return ((instId_ == InstId::ret) || (instId_ == InstId::br) ||
          (instId_ == InstId::store) ||
          (instId_ == InstId::call && getType()->isVoidType()));
}

bool Instruction::isPhi() { return instId_ == InstId::phi; }
bool Instruction::isStore() { return instId_ == InstId::store; }
bool Instruction::isAlloca() { return instId_ == InstId::alloca; }
bool Instruction::isRet() { return instId_ == InstId::ret; }
bool Instruction::isLoad() { return instId_ == InstId::load; }
bool Instruction::isBr() { return instId_ == InstId::br; }

bool Instruction::isAdd() { return instId_ == InstId::add; }
bool Instruction::isSub() { return instId_ == InstId::sub; }
bool Instruction::isMul() { return instId_ == InstId::mul; }
bool Instruction::isDiv() { return instId_ == InstId::sdiv; }

bool Instruction::isFadd() { return instId_ == InstId::fadd; }
bool Instruction::isFsub() { return instId_ == InstId::fsub; }
bool Instruction::isFmul() { return instId_ == InstId::fmul; }
bool Instruction::isFdiv() { return instId_ == InstId::fdiv; }
bool Instruction::isFp2si() { return instId_ == InstId::fptosi; }
bool Instruction::isSi2fp() { return instId_ == InstId::sitofp; }

bool Instruction::isIcmp() { return instId_ == InstId::icmp; }
bool Instruction::isFcmp() { return instId_ == InstId::fcmp; }

bool Instruction::isCall() { return instId_ == InstId::call; }
bool Instruction::isGep() { return instId_ == InstId::getelementptr; }
bool Instruction::isZext() { return instId_ == InstId::zext; }

bool Instruction::isBinary() {
  return (isAdd() || isSub() || isMul() || isDiv() || isFadd() || isFsub() ||
          isFmul() || isFdiv()) &&
         (getOperandNum() == 2);
}

bool Instruction::isTerminator() { return isBr() || isRet(); }

std::string Instruction::getInstructionOpName() {
  std::string instName;
  switch (instId_) {
  case InstId::ret:
    instName = "ret";
    break;
  case InstId::br:
    instName = "br";
    break;
  case InstId::add:
    instName = "add";
    break;
  case InstId::sub:
    instName = "sub";
    break;
  case InstId::mul:
    instName = "mul";
    break;
  case InstId::sdiv:
    instName = "sdiv";
    break;
  case InstId::fadd:
    instName = "fadd";
    break;
  case InstId::fsub:
    instName = "fsub";
    break;
  case InstId::fmul:
    instName = "fmul";
    break;
  case InstId::fdiv:
    instName = "fdiv";
    break;
  case InstId::alloca:
    instName = "alloca";
    break;
  case InstId::load:
    instName = "load";
    break;
  case InstId::store:
    instName = "store";
    break;
  case InstId::icmp:
    instName = "cmp";
    break;
  case InstId::fcmp:
    instName = "fcmp";
    break;
  case InstId::phi:
    instName = "phi";
    break;
  case InstId::call:
    instName = "call";
    break;
  case InstId::getelementptr:
    instName = "getelementptr";
    break;
  case InstId::zext:
    instName = "zext";
    break;
  case InstId::fptosi:
    instName = "fptosi";
    break;
  case InstId::sitofp:
    instName = "sitofp";
    break;
  default:
    break;
  }
  return instName;
}