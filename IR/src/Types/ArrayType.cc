#include "Types/ArrayType.h"
#include "Context.h"
#include <cassert>

ArrayType::ArrayType(Type *elementType, std::size_t elementNum)
    : Type(TypeId::ArrayTypeId), elementType_(elementType),
      elementNum_(elementNum) {}

ArrayType *ArrayType::get(Context &context, Type *elementType,
                          std::size_t elementNum) {
  return context.getArrayType(elementType, elementNum);
}

ArrayType *ArrayType::get(Context &context, Type *elementType,
                          std::vector<int> dimension) {
  assert(dimension.size() != 0);
  ArrayType *arr_type;
  int i = dimension.size() - 1;
  arr_type = ArrayType::get(context, elementType, dimension[i--]);
  for (; i >= 0; i--) {
    arr_type = ArrayType::get(context, arr_type, dimension[i]);
  }
  return arr_type;
}

Type *ArrayType::getElementType() { return elementType_; }

std::size_t ArrayType::getElementNum() { return elementNum_; }
