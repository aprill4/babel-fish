#include "Types/FunctionType.h"

FunctionType::FunctionType(Type *resultType, std::vector<Type *> argumentsType)
    : Type(TypeId::FunctionTypeId), resultType_(resultType),
      argumentsType_(argumentsType) {}

std::size_t FunctionType::getArgumentsNum() { return argumentsType_.size(); }

Type *FunctionType::getReturnType() { return resultType_; }