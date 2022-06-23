#include "../../include/Types/FunctionType.h"

FunctionType::FunctionType(Type *result, std::vector<Type *> args)
    : Type(TypeId::FunctionTypeId), result_(result), args_(args) {}
