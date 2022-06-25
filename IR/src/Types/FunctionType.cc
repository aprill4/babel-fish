#include "Types/FunctionType.h"

FunctionType::FunctionType(Type *resultType)
    : Type(TypeId::FunctionTypeId), resultType_(resultType) {}

FunctionType::FunctionType(Type *resultType, std::vector<Type *> argumentsType)
    : Type(TypeId::FunctionTypeId), resultType_(resultType),
      argumentsType_(argumentsType) {}

FunctionType *FunctionType::get(Type *resultType) {
  return new FunctionType(resultType);
}

FunctionType *FunctionType::get(Type *resultType,
                                std::vector<Type *> paramsType) {
  return new FunctionType(resultType, paramsType);
}

std::size_t FunctionType::getArgumentsNum() { return argumentsType_.size(); }

Type *FunctionType::getReturnType() { return resultType_; }

Type *FunctionType::getArgumentType(std::size_t idx) {
  return argumentsType_[idx];
}
