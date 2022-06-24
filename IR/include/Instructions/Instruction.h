#pragma once
#include "../User.h"
#include "../Types/Type.h"

class BasicBlock;
class Module;

class Instruction : public User {
public:
  enum class OpId {
    // Terminator Instructions
    ret,
    br,
    // Standard binary operators
    add,
    sub,
    mul,
    sdiv,
    // float binary operators
    fadd,
    fsub,
    fmul,
    fdiv,
    // Memory operators
    alloca,
    load,
    store,
    // Other operators
    icmp,
    fcmp,
    phi,
    call,
    getelementptr,
    zext, // zero extend
    fptosi,
    sitofp
    // float binary operators Logical operators
  };
  Instruction(Type *type, OpId opId, std::size_t operandNum, BasicBlock *parent,
              const std::string &name = "");
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