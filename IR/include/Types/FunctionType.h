#pragma once
#include "Type.h"
#include <vector>

class FunctionType : public Type {
public:
  FunctionType(Type *resultType);
  FunctionType(Type *resultType, std::vector<Type *> argumentsType_);
  static FunctionType *get(Type *resultType);
  static FunctionType *get(Type *resultType, std::vector<Type *> paramsType);
  std::size_t getArgumentsNum();
  Type *getReturnType();

private:
  Type *resultType_;
  std::vector<Type *> argumentsType_;
};