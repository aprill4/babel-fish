#pragma once
#include "../Types/Type.h"
#include "../User.h"

class BasicBlock;
class Module;

class Instruction : public User {
public:
  enum class OpId {
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
  Instruction(Type *type, OpId opId, std::size_t operandNum,
              BasicBlock *parent);
  Module *getModule();

  OpId getInstrcutionType() { return opId_; }
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
  OpId opId_;
};