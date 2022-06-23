#include "../../include/Types/ArrayType.h"

ArrayType::ArrayType(Type *elementType, std::size_t elementNum)
    : Type(TypeId::ArrayTypeId), elementType_(elementType),
      elementNum_(elementNum) {}

Type *ArrayType::getElementType() { return elementType_; }

std::size_t ArrayType::getElementNum() { return elementNum_; }
