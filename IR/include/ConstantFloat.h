#pragma once

#include "Constant.h"

class Context;

class ConstantFloat : public Constant {
public:
  ConstantFloat(Type *type, double value)
      : Constant(type, "", 0), value_(value) {}
  double get_value() { return value_; }
  std::string print() override;

public:
  static ConstantFloat *get(Context &context, double value);

private:
  double value_;
};
