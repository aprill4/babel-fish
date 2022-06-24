#pragma once
#include "Value.h"

class BasicBlock;
class Argument;
class Module;
class FunctionType;

class Function : public Value {
public:
  Function(FunctionType *ty, const std::string &name, Module *parent);
  ~Function();
  Module *getParent();

private:
  //   std::list<BasicBlock *> basic_blocks_; // basic blocks
  //   std::list<Argument *> arguments_;      // arguments
  Module *parent_;
};