#pragma once

#include "Constant.h"
#include <iostream>

class ConstantInt : public Constant {
public:
  ConstantInt(Type *type, ssize_t value) : Constant(type, "", 0), value_(value) {}
  ssize_t getValue() { return value_; }
  std::string print() override;
private:
  ssize_t value_;
};
