#include "User.h"
#include "Type.h"
#include "Use.h"
#include "Util.h"
#include <cassert>

User::User(Type *type, const std::string &name, std::size_t operandNum)
    : Value(type, name), operandNum_(operandNum), operands_(operandNum) {}

std::size_t User::getOperandNum() { return operandNum_; }

Value *User::getOperand(std::size_t idx) { return operands_[idx]; }

Type *User::getOperandType(std::size_t idx) {
  return operands_[idx]->getType();
}

std::string User::getOperandTypeName(std::size_t idx) {
  return operands_[idx]->getType()->getTypeName();
}

void User::setOperand(Value *value, std::size_t idx) {
  assert(idx < operandNum_ && "setOperand out of index");
  operands_[idx] = value;
  value->addUse(Use(this, value));
}

void User::addOperand(Value *value) {
  operands_.emplace_back(value);
  value->addUse(Use(this, value));
  operandNum_++;
}