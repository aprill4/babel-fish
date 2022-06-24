#include "Module.h"
#include "Function.h"
#include "GlobalVariable.h"
#include "Types/FloatType.h"
#include "Types/IntegerType.h"
#include "Types/Type.h"
#include <iostream>

Module::Module(const std::string &moduleName) : moduleName_(moduleName) {
  voidType_ = new Type(Type::TypeId::VoidTypeId);
  labelType_ = new Type(Type::TypeId::LabelTypeId);
  int1Type_ = new IntegerType(1);
  int32Type_ = new IntegerType(32);
  float32Type_ = new FloatType();
}

void Module::addFuntion(Function *func) { functionList_.emplace_back(func); }

void Module::addGlobalVariable(GlobalVariable *gVariable) {
  globalVariableList_.emplace_back(gVariable);
}

std::string Module::print() {
  std::string module_ir;
  for (auto global_val : globalVariableList_) {
    // module_ir += global_val->print();
    // module_ir += "\n";
  }
  for (auto &func : functionList_) {
    module_ir += func->print();
    module_ir += "\n";
  }
  return module_ir;
}