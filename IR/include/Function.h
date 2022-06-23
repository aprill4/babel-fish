#pragma once
#include "Value.h"

class BasicBlock;
class Argument;
class Module;
class Function : public Value {
public:
  Module *getParent();

private:
  //   std::list<BasicBlock *> basic_blocks_; // basic blocks
  //   std::list<Argument *> arguments_;      // arguments
    Module *parent_;
};