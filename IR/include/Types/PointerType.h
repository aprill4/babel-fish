#pragma once
#include "Type.h"

class PointerType : public Type {
public:
  PointerType(Type *ptrElementType);
  Type *getPtrElementType();

public:
  static PointerType *get(Context &context, Type *ptrElementType);

private:
  Type *ptrElementType_;
};