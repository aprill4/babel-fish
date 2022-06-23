#include "../include/Module.h"

inline Module::Module(const std::string& moduleName) : moduleName_(moduleName) {
    
}

inline void Module::addFuntion(Function *func) { functionList_.emplace_back(func); }

inline void Module::addGlobalVariable(GlobalVariable *gVariable) {
  globalVariableList_.emplace_back(gVariable);
}