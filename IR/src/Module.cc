#include "../include/Module.h"

Module::Module(const std::string &moduleName) : moduleName_(moduleName) {}

void Module::addFuntion(Function *func) { functionList_.emplace_back(func); }

void Module::addGlobalVariable(GlobalVariable *gVariable) {
  globalVariableList_.emplace_back(gVariable);
}