#pragma once
#include "User.h"

class Constant : public User {
public:
  Constant(Context &c, Type *type, const std::string &name = "", std::size_t operandNum = 0)
      : User(c, type, name, operandNum) {}
};