#pragma once
#include "Value.h"
#include <vector>

class BasicBlock;
class Argument;
class Module;
class FunctionType;

class Function : public Value {
public:
  Function(Context &c, FunctionType *funcType, const std::string args_name[], const std::string &funcName, Module *parent);

  Module *getModule();
  Type *getReturnType();

  std::size_t getArgumentsNum();
  FunctionType *getFunctionType();

  void addBasicBlock(BasicBlock *bb);
  std::list<BasicBlock *>& getBasicBlocks();

  void remove(BasicBlock* bb);
  Argument *getArgument(size_t idx);

  std::string print() override;

public:
  static Function *Create(Context &c, FunctionType *funcType, const std::string args_name[], const std::string &funcName,
                          Module *parent);

private:
  Module *parent_;
  std::list<BasicBlock *> basicBlocks_;
  std::vector<Argument *> arguments_; // formalArgs
};