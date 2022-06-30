#pragma once
#include "../Types/Type.h"
#include "../User.h"

class BasicBlock;
class Module;

class Instruction : public User {
public:
  enum class InstId {
    Ret,
    Br,
    Add,
    Sub,
    Mul,
    Sdiv,
    Fadd,
    Fsub,
    Fmul,
    Fdiv,
    And,
    Or,
    Alloca,
    Load,
    Store,
    Icmp,
    Fcmp,
    Phi,
    Call,
    Getelementptr,
    Zext,
    Fptosi,
    Sitofp
  };

  Instruction(Type *type, InstId instId, std::size_t operandNum, BasicBlock *parent);
  
  Instruction(Type *type, InstId instId, std::size_t operandNum, BasicBlock *parent, std::string name);

  Instruction(Context &c, Type *type, InstId instId, std::size_t operandNum,
              BasicBlock *parent, std::string name);

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