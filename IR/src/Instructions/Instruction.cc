#include "Instructions/Instruction.h"
#include "BasicBlock.h"

Instruction::Instruction(Type *type, InstId instId, std::size_t operandNum,
                         BasicBlock *parent)
    : User(type, "", operandNum), instId_(instId), parent_(parent) {}

Instruction::Instruction(Type *type, InstId instId, std::size_t operandNum,
                         BasicBlock *parent, std::string name)
    : User(type, name, operandNum), instId_(instId), parent_(parent) {}

Instruction::Instruction(Context &c, Type *type, InstId instId, std::size_t operandNum,
                         BasicBlock *parent, std::string name)
    : User(c, type, name, operandNum), instId_(instId), parent_(parent) {}

Module *Instruction::getModule() { return parent_->getModule(); }

bool Instruction::isVoid() {
  return ((instId_ == InstId::Ret) || (instId_ == InstId::Br) ||
          (instId_ == InstId::Store) ||
          (instId_ == InstId::Call && getType()->isVoidType()));
}

bool Instruction::isPhi() { return instId_ == InstId::Phi; }
bool Instruction::isStore() { return instId_ == InstId::Store; }
bool Instruction::isAlloca() { return instId_ == InstId::Alloca; }
bool Instruction::isRet() { return instId_ == InstId::Ret; }
bool Instruction::isLoad() { return instId_ == InstId::Load; }
bool Instruction::isBr() { return instId_ == InstId::Br; }

bool Instruction::isAdd() { return instId_ == InstId::Add; }
bool Instruction::isSub() { return instId_ == InstId::Sub; }
bool Instruction::isMul() { return instId_ == InstId::Mul; }
bool Instruction::isDiv() { return instId_ == InstId::Sdiv; }
bool Instruction::isMod() { return instId_ == InstId::Mod; }

bool Instruction::isAnd() { return instId_ == InstId::And; }
bool Instruction::isOr() { return instId_ == InstId::Or; }

bool Instruction::isFadd() { return instId_ == InstId::Fadd; }
bool Instruction::isFsub() { return instId_ == InstId::Fsub; }
bool Instruction::isFmul() { return instId_ == InstId::Fmul; }
bool Instruction::isFdiv() { return instId_ == InstId::Fdiv; }
bool Instruction::isFp2si() { return instId_ == InstId::Fptosi; }
bool Instruction::isSi2fp() { return instId_ == InstId::Sitofp; }

bool Instruction::isIcmp() { return instId_ == InstId::Icmp; }
bool Instruction::isFcmp() { return instId_ == InstId::Fcmp; }

bool Instruction::isCall() { return instId_ == InstId::Call; }
bool Instruction::isGep() { return instId_ == InstId::Getelementptr; }
bool Instruction::isZext() { return instId_ == InstId::Zext; }

bool Instruction::isBinary() {
  return (isAdd() || isSub() || isMul() || isDiv() || isMod() || isFadd() || isFsub() ||
          isFmul() || isFdiv() || isAnd() || isOr() || isIcmp() || isFcmp()) &&
         (getOperandNum() == 2);
}

bool Instruction::isTerminator() { return isBr() || isRet(); }

std::string Instruction::getInstructionOpName() {
  std::string instName;
  switch (instId_) {
  case InstId::Ret:
    instName = "ret";
    break;
  case InstId::Br:
    instName = "br";
    break;
  case InstId::Add:
    instName = "add";
    break;
  case InstId::Sub:
    instName = "sub";
    break;
  case InstId::Mul:
    instName = "mul";
    break;
  case InstId::Sdiv:
    instName = "sdiv";
    break;
  case InstId::Mod:
    instName = "mod";
    break;
  case InstId::Fadd:
    instName = "fadd";
    break;
  case InstId::Fsub:
    instName = "fsub";
    break;
  case InstId::Fmul:
    instName = "fmul";
    break;
  case InstId::Fdiv:
    instName = "fdiv";
    break;
  case InstId::And:
    instName = "and";
    break;
  case InstId::Or:
    instName = "or";
    break;
  case InstId::Alloca:
    instName = "alloca";
    break;
  case InstId::Load:
    instName = "load";
    break;
  case InstId::Store:
    instName = "store";
    break;
  case InstId::Icmp:
    instName = "cmp";
    break;
  case InstId::Fcmp:
    instName = "fcmp";
    break;
  case InstId::Phi:
    instName = "phi";
    break;
  case InstId::Call:
    instName = "call";
    break;
  case InstId::Getelementptr:
    instName = "getelementptr";
    break;
  case InstId::Zext:
    instName = "zext";
    break;
  case InstId::Fptosi:
    instName = "fptosi";
    break;
  case InstId::Sitofp:
    instName = "sitofp";
    break;
  default:
    break;
  }
  return instName;
}