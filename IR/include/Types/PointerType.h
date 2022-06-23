#pragma once
#include "Type.h"

class PointerType : public Type {
public:
  PointerType(Type *pElementType);

  Type *getElementType();

private:
  Type *pElementType_;
};