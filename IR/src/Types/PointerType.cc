#include "Types/PointerType.h"
#include "Context.h"

PointerType::PointerType(Type *ptrElementType)
    : Type(TypeId::PointerTypeId), ptrElementType_(ptrElementType) {}

PointerType *PointerType::get(Context &context, Type *ptrElementType) {
  return context.getPtrType(ptrElementType);
}

Type *PointerType::getPtrElementType() { return ptrElementType_; }