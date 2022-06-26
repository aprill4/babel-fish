#include "Module.h"
#include "Context.h"
#include "Function.h"
#include "GlobalVariable.h"
#include "Types/IntegerType.h"
#include "Types/Type.h"
#include <iostream>

Module::Module(Context &context, const std::string &moduleName)
    : context_(context), moduleName_(moduleName) {
  context_.addModule(this);
}

void Module::addFuntion(Function *func) { functionList_.emplace_back(func); }

void Module::addGlobalVariable(GlobalVariable *globalVariable) {
  globalVariableList_.emplace_back(globalVariable);
}

std::string Module::print() {
  std::string module_ir;
  for (auto global_val : globalVariableList_) {
    module_ir += global_val->print();
    module_ir += "\n";
  }
  for (auto &func : functionList_) {
    module_ir += func->print();
    module_ir += "\n";
  }
  return module_ir;
}