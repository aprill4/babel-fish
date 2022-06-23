#pragma once

#include <string>
#include <vector>

class GlobalVariable;
class Function;

class Module {
public:
  explicit Module(const std::string moduleName);

private:
  std::string moduleName_;
  std::vector<GlobalVariable *> globalVariableList_;
  std::vector<Function *> functionList_;
};