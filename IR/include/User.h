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
  Type *getOperandType(std::size_t idx);
  std::string getOperandTypeName(std::size_t idx);

  void setOperand(Value* value, std::size_t idx);
  void addOperand(Value* value);
private:
  std::vector<Value *> operands_;
  std::size_t operandNum_;
};
