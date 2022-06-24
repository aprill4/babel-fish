#pragma once

#include <string>
#include <utility>

class Type {
public:
  enum class TypeId {
    VoidTypeId,
    FloatTypeId,
    IntegerTypeId,
    FunctionTypeId,
    ArrayTypeId,
    LabelTypeId,
    PointerTypeId
  };

public:
  explicit Type(TypeId typdId);
  ~Type() = default;
  TypeId getTypeId() { return typeId_; }
  bool isVoidType() { return typeId_ == TypeId::VoidTypeId; }
  bool isFloatType() { return typeId_ == TypeId::FloatTypeId; }
  bool isIntegerType() { return typeId_ == TypeId::IntegerTypeId; }
  bool isFunctionType() { return typeId_ == TypeId::FunctionTypeId; }
  bool isArrayType() { return typeId_ == TypeId::ArrayTypeId; }
  bool isLabelType() { return typeId_ == TypeId::LabelTypeId; }
  bool isPointerType() { return typeId_ == TypeId::PointerTypeId; }
  std::string getTypeName();
  Type *getPtrElementType();
  static bool isEqType(Type *typeL, Type *typeR);

private:
  TypeId typeId_;
};