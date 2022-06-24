#pragma once
#include "Type.h"
#include <vector>

class FunctionType : public Type {
public:
  FunctionType(Type *resultType, std::vector<Type *> argumentsType_);
  std::size_t getArgumentsNum();
  Type *getReturnType();

private:
  Type *resultType_;
  std::vector<Type *> argumentsType_;
};