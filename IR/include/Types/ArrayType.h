#pragma once

#include "Type.h"

class ArrayType : public Type {
public:
  ArrayType(Type *elementType, std::size_t elementNum);
  Type *getElementType();
  std::size_t getElementNum();

private:
  Type *elementType_;
  std::size_t elementNum_;
};