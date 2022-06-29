#pragma once
#include "../Types/Type.h"
#include "../User.h"

class BasicBlock;
class Module;

class Instruction : public User {
public:
  enum class InstId {
    ret,
    br,
    add,
    sub,
    mul,
    sdiv,
    fadd,
    fsub,
    fmul,
    fdiv,
    and,
    or,
    alloca,
    load,
    store,
    icmp,
    fcmp,
    phi,
    call,
    getelementptr,
    zext,
    fptosi,
    sitofp
  };
  Instruction(Type *type, InstId instId, std::size_t operandNum,
              BasicBlock *parent);
  Module *getModule();

  InstId getInstrcutionType() { return instId_; }
  std::string getInstructionOpName();

  bool isPhi();
  bool isStore();
  bool isAlloca();
  bool isRet();
  bool isLoad();
  bool isBr();

  bool isAdd();
  bool isSub();
  bool isMul();
  bool isDiv();

  bool isFadd();
  bool isFsub();
  bool isFmul();
  bool isFdiv();

  bool isAnd();
  bool isOr();

  bool isFp2si();
  bool isSi2fp();

  bool isIcmp();
  bool isFcmp();

  bool isCall();
  bool isGep();
  bool isZext();

  bool isVoid();
  bool isBinary();
  bool isTerminator();

private:
  BasicBlock *parent_;
  InstId instId_;
};