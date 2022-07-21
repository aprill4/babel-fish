#pragma once

#include "Constant.h"

class Context;

class ConstantFloat : public Constant {
public:
  ConstantFloat(Context &c, Type *type, float value)
      : Constant(c, type, "", 0), value_(value) {}
  float getValue() { return value_; }
  void setValue(float value) { value_ = value; }
  std::string print() override;

public:
  static ConstantFloat *get(Context &context, float value);

private:
  float value_;
};
