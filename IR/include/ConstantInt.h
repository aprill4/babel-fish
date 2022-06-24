#pragma once

#include "Constant.h"
#include <iostream>

class ConstantInt : public Constant {
public:
  ConstantInt(Type *ty, ssize_t val) : Constant(ty, "", 0), value_(val) {}
  std::string print() override;
  ssize_t getValue() { return value_; }

private:
  ssize_t value_;
};
