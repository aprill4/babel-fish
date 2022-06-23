#pragma once
#include "Type.h"
#include <vector>

class FunctionType : public Type {
public:
  FunctionType(Type *result, std::vector<Type *> args);

private:
  Type *result_;
  std::vector<Type *> args_;
};