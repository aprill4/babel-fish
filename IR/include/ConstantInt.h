#pragma once

#include "Constant.h"
#include <iostream>

class ConstantInt : public Constant {
public:
  ConstantInt(Context &c, Type *type, ssize_t value)
      : Constant(c, type, "", 0), value_(value) {}
  ssize_t getValue() { return value_; }
  std::string print() override;

public:
  static ConstantInt *get(Context &c, Type *type, ssize_t value) {
    return new ConstantInt(c, type, value);
  }

private:
  ssize_t value_;
};
