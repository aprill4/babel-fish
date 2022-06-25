#pragma once
#include "Value.h"
#include <vector>

class BasicBlock;
class Argument;
class Module;
class FunctionType;

class Function : public Value {
public:
  Function(FunctionType *funcType, const std::string &funcName, Module *parent);
  Module *getModule();
  Type *getReturnType();
  std::size_t getArgumentsNum();
  FunctionType *getFunctionType();
  void addBasicBlock(BasicBlock *bb);
  std::string print() override;

public:
  static Function *Create(FunctionType *funcType, const std::string &funcName,
                          Module *parent);

private:
  Module *parent_;
  std::list<BasicBlock *> basicBlocks_;
  std::vector<Argument *> arguments_; // formalArgs
};