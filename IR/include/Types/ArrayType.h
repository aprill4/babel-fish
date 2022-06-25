#pragma once

#include "Type.h"
class Context;

class ArrayType : public Type {
public:
  ArrayType(Type *elementType, std::size_t elementNum);
  Type *getElementType();
  std::size_t getElementNum();

public:
  static ArrayType *get(Context &context, Type *elementType,
                        std::size_t elementNum);

private:
  Type *elementType_;
  std::size_t elementNum_;
};