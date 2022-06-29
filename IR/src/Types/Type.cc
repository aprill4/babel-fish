#include "Types/Type.h"
#include "Context.h"
#include "Types/ArrayType.h"
#include "Types/FunctionType.h"
#include "Types/IntegerType.h"
#include "Types/PointerType.h"
#include <stdio.h>

Type::Type(TypeId typdId) : typeId_(typdId) {}

bool Type::operator==(const Type &type) { return typeId_ == type.typeId_; }

Type *Type::getVoidType(Context &context) { return context.VoidType; }

Type *Type::getLabelType(Context &context) { return context.LabelType; }

IntegerType *Type::getInt1Type(Context &context) { return context.Int1Type; }

IntegerType *Type::getInt32Type(Context &context) { return context.Int32Type; }

Type *Type::getFloatType(Context &context) { return context.FloatType; }

PointerType *Type::getPtrType(Context &context, Type *ptrElementType) {
  return PointerType::get(context, ptrElementType);
}

ArrayType *Type::getArrayType(Context &context, Type *elementType,
                              std::size_t elementNum) {
  return ArrayType::get(context, elementType, elementNum);
}

std::string Type::getTypeName() {
  std::string typeName;
  switch (typeId_) {
  case TypeId::VoidTypeId:
    typeName = "void";
    break;
  case TypeId::LabelTypeId:
    typeName = "label";
    break;
  case TypeId::IntegerTypeId:
    typeName +=
        "i" + std::to_string(static_cast<IntegerType *>(this)->getBitsNum());
    break;
  case TypeId::FunctionTypeId:
    typeName +=
        static_cast<FunctionType *>(this)->getReturnType()->getTypeName();
    typeName += " (";
    for (int i = 0; i < static_cast<FunctionType *>(this)->getArgumentsNum();
         i++) {
      if (i)
        typeName += ", ";
      typeName +=
          static_cast<FunctionType *>(this)->getArgumentType(i)->getTypeName();
    }
    typeName += ")";
    break;
  case TypeId::PointerTypeId:
    typeName += this->getPtrElementType()->getTypeName();
    typeName += "*";
    break;
  case TypeId::ArrayTypeId:
    typeName += "[";
    typeName += std::to_string(static_cast<ArrayType *>(this)->getElementNum());
    typeName += " x ";
    typeName += static_cast<ArrayType *>(this)->getElementType()->getTypeName();
    typeName += "]";
    break;
  case TypeId::FloatTypeId:
    typeName += "float";
    break;
  default:
    break;
  }
  return typeName;
}

Type *Type::getPtrElementType() {
  if (this->isPointerType())
    return static_cast<PointerType *>(this)->getPtrElementType();
  else
    return nullptr;
}
