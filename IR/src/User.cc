#include "../include/User.h"

User::User(Type *type, const std::string &name, std::size_t operandNum)
    : Value(type, name), operandNum_(operandNum) {}

std::size_t User::getOperandNum() { return operandNum_; }

Value *User::getOperand(std::size_t idx) { return operands_[idx]; }