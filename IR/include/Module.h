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

class Module {
public:
  explicit Module(const std::string &moduleName);
  ~Module() = default;
  void addFuntion(Function *func);
  void addGlobalVariable(GlobalVariable *gVariable);

  Type *getLabelType() { return labelType_; }
  Type *getVoidType() { return voidType_; }
  IntegerType *getInt1Type() { return int1Type_; }
  IntegerType *getInt32Type() { return int32Type_; }
  FloatType *getFloatType() { return float32Type_; }
  std::string print();

private:
  Type *labelType_;
  Type *voidType_;
  IntegerType *int1Type_;
  IntegerType *int32Type_;
  FloatType *float32Type_;

private:
  std::string moduleName_;
  std::vector<GlobalVariable *> globalVariableList_;
  std::vector<Function *> functionList_;
  std::map<std::string, Value *> symbolTable_;
};