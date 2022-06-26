#pragma once

#include "Constant.h"
#include <iostream>

class ConstantInt : public Constant {
public:
  ConstantInt(Type *type, ssize_t value)
      : Constant(type, "", 0), value_(value) {}
  ssize_t getValue() { return value_; }
  std::string print() override;

public:
  static ConstantInt *get(Type *type, ssize_t value) {
    return new ConstantInt(type, value);
  }

private:
  ssize_t value_;
};
