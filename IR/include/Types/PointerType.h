#pragma once
#include "Type.h"

class PointerType : public Type {
public:
  PointerType(Type *ptrElementType);

  Type *getPtrElementType();

private:
  Type *ptrElementType_;
};