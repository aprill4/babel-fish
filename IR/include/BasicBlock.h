#pragma once
#include "Type.h"
#include "Value.h"

class Instruction;
class Module;
class Function;

class BasicBlock : public Value {
public:
  BasicBlock(Context &context, const std::string &name, Function *parent);
  Module *getModule();
  std::string print() override;
  void addInstruction(Instruction *instruction);

public:
  static BasicBlock *Create(Context &context, const std::string &name,
                            Function *parent);

private:
  Function *parent_;
  std::list<BasicBlock *> predecessorBlocks_;
  std::list<BasicBlock *> successorBlocks_;
  std::list<Instruction *> instructionList_;
};