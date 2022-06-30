#pragma once

#include "Constant.h"

class Context;

class ConstantZero : public Constant {
public:
  ConstantZero(Context &c, Type *type) : Constant(c, type, "", 0) {}
  std::string print() override;

public:
  static ConstantZero *get(Context &c, Type *type);

private:
};