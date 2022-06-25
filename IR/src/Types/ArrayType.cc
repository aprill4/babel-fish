#include "Types/ArrayType.h"
#include "Context.h"

ArrayType::ArrayType(Type *elementType, std::size_t elementNum)
    : Type(TypeId::ArrayTypeId), elementType_(elementType),
      elementNum_(elementNum) {}

ArrayType *ArrayType::get(Context &context, Type *elementType,
                          std::size_t elementNum) {
  return context.getArrayType(elementType, elementNum);
}

Type *ArrayType::getElementType() { return elementType_; }

std::size_t ArrayType::getElementNum() { return elementNum_; }
