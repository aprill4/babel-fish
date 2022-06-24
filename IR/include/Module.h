#pragma once

#include <iterator>
#include <map>
#include <string>
#include <vector>

class GlobalVariable;
class Function;
class Value;

class Module {
  typedef std::vector<Function *>::iterator func_iterator;
  typedef std::vector<Function *>::const_iterator func_const_iterator;
  typedef std::vector<GlobalVariable *>::iterator global_iterator;
  typedef std::vector<GlobalVariable *>::const_iterator global_const_iterator;

public:
  explicit Module(const std::string &moduleName);
  ~Module() = default;
  void addFuntion(Function *func);
  void addGlobalVariable(GlobalVariable *gVariable);

  func_iterator func_begin() { return functionList_.begin(); }
  func_const_iterator func_begin() const { return functionList_.begin(); }
  func_iterator func_end() { return functionList_.end(); }
  func_const_iterator func_end() const { return functionList_.end(); }
  size_t func_size() const { return functionList_.size(); }
  bool func_empty() const { return functionList_.empty(); }

  global_iterator global_begin() { return globalVariableList_.begin(); }
  global_const_iterator global_begin() const {
    return globalVariableList_.begin();
  }
  global_iterator global_end() { return globalVariableList_.end(); }
  global_const_iterator global_end() const { return globalVariableList_.end(); }
  size_t global_size() const { return globalVariableList_.size(); }
  bool global_empty() const { return globalVariableList_.empty(); }

private:
  std::string moduleName_;
  std::vector<GlobalVariable *> globalVariableList_;
  std::vector<Function *> functionList_;
  std::map<std::string, Value *> symbolTable_;
};