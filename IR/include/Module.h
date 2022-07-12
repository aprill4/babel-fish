#pragma once

#include <iterator>
#include <map>
#include <string>
#include <set>
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

public:
  Context &context_;
  std::string moduleName_;
  std::set<GlobalVariable *> globalVariableList_;
  std::vector<Function *> functionList_;
  std::map<std::string, Value *> symbolTable_;
};