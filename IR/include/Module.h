#pragma once

#include <iterator>
#include <map>
#include <string>
#include <vector>

class GlobalVariable;
class Function;
class Value;
class Type;
class FloatType;
class IntegerType;
class Context;

class Module {
public:
  Module(Context &context, const std::string &moduleName);
  void addFuntion(Function *func);
  void addGlobalVariable(GlobalVariable *globalVariable);
  std::string print();

private:
  Context &context_;
  std::string moduleName_;
  std::vector<GlobalVariable *> globalVariableList_;
  std::vector<Function *> functionList_;
  //std::map<std::string, Value *> symbolTable_;
};