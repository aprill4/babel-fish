#pragma once
#include "Type.h"
#include "Value.h"
#include <set>

class Instruction;
class Module;
class Function;

class BasicBlock : public Value {
public:
  BasicBlock(Context &context, const std::string &name, Function *parent);
  Module *getModule();
  std::string print() override;

  void addInstruction(Instruction *instruction);
  void addPredecessor(BasicBlock* pre);
  void addSuccessor(BasicBlock* suc);

  void addDominator(BasicBlock *dom);
  void setDominators(std::set<BasicBlock *> &doms);
  std::set<BasicBlock *>& getDominators();

  std::list<BasicBlock *>& getPredecessors();

  bool hasTerminator();
  void eraseFromParent();

public:
  static BasicBlock *Create(Context &context, const std::string &name,
                            Function *parent);

private:
  Function *parent_;
  std::list<BasicBlock *> predecessorBlocks_;
  std::list<BasicBlock *> successorBlocks_;
  std::list<Instruction *> instructionList_;
  std::set<BasicBlock *> dominators_;
};