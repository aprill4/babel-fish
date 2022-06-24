#pragma once
#include "Value.h"

class BasicBlock;
class Argument;
class Module;
class FunctionType;

class Function : public Value {
public:
  Function(const std::string &name, FunctionType *type, Module *parent);
  ~Function() = default;
  Module *getParent();
  Type *getReturnType();
  std::size_t getArgumentsNum();
  FunctionType *getFunctionType();
  std::string print() override;

private:
  Module *parent_;
  std::list<BasicBlock *> basic_blocks_; // basic blocks
  std::list<Argument *> arguments_;      // arguments
};