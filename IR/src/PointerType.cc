#include "../include/PointerType.h"

PointerType::PointerType(Type *pElementType)
    : Type(TypeId::PointerTypeId), pElementType_(pElementType) {}

Type *PointerType::getElementType() { return pElementType_; }