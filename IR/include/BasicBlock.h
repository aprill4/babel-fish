#pragma once
#include "Value.h"

class Instruction;
class Module;
class Function;

class BasicBlock : Value {
public:
  BasicBlock(const std::string &name, Function *parent);
  Module *getModule();
  std::string print() override;
  void addInstruction(Instruction *instruction);

private:
  Function *parent_;
  std::list<BasicBlock *> predecessorBlocks_;
  std::list<BasicBlock *> successorBlocks_;
  std::list<Instruction *> instructionList_;
};