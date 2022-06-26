#pragma once

#include "Constant.h"

class Context;

class ConstantZero : public Constant {
public:
  ConstantZero(Type *type) : Constant(type, "", 0) {}
  std::string print() override;

public:
  static ConstantZero *get(Type *type);

private:
};