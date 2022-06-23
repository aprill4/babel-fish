#pragma once

#include "Value.h"
#include <vector>

class Use;

class User : public Value {
public:
  User(Type *type, const std::string &name = "", std::size_t operandNum = 0);
  ~User() = default;
  std::size_t getOperandNum();
  Value *getOperand(std::size_t idx);

private:
  std::vector<Value *> operands_;
  std::size_t operandNum_;
  std::list<Use> operandList_;
};
