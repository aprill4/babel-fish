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
  Module *getModule();
  Type *getReturnType();
  std::size_t getArgumentsNum();
  FunctionType *getFunctionType();
  void addBasicBlock(BasicBlock *bb);
  std::string print() override;

private:
  Module *parent_;
  std::list<BasicBlock *> basicBlocks_;
  std::list<Argument *> arguments_;
};