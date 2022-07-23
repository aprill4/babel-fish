#pragma once

#include "Type.h"
#include <vector>
class Context;

class ArrayType : public Type {
public:
  ArrayType(Type *elementType, std::size_t elementNum);
  Type *getElementType();
  std::size_t getElementNum();

public:
  static ArrayType *get(Context &context, Type *elementType,
                        std::size_t elementNum);
  static ArrayType *get(Context &context, Type *elementType,
                        std::vector<int> dimension);
private:
  Type *elementType_;
  //total number of elements, -1 is reserved for the situation when the first dimension is unknown 
  std::size_t elementNum_;
};