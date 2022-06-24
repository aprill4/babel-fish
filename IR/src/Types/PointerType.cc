#include "../../include/Types/PointerType.h"

PointerType::PointerType(Type *ptrElementType)
    : Type(TypeId::PointerTypeId), ptrElementType_(ptrElementType) {}

Type *PointerType::getPtrElementType() { return ptrElementType_; }