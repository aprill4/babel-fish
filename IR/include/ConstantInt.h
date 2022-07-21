#pragma once

#include "Constant.h"
#include <iostream>

class ConstantInt : public Constant {
public:
  ConstantInt(Context &c, Type *type, int32_t value)
      : Constant(c, type, "", 0), value_(value) {}
  ssize_t getValue() { return value_; }
  void setValue(int32_t value) { value_ = value; }
  std::string print() override;

public:
  static ConstantInt *get(Context &c, Type *type, int32_t value) {
    return new ConstantInt(c, type, value);
  }

private:
  int32_t value_;
};
