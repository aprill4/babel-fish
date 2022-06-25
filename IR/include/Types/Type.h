#pragma once

#include <string>
#include <utility>

class FloatType;
class IntegerType;
class ArrayType;
class Context;
class PointerType;

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
  bool operator==(const Type &type);
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

  static Type *getVoidType(Context &context);
  static Type *getLabelType(Context &context);
  static Type *getFloatType(Context &context);
  static IntegerType *getInt1Type(Context &context);
  static IntegerType *getInt32Type(Context &context);
  static PointerType *getPtrType(Context &context, Type *ptrElementType);
  static ArrayType *getArrayType(Context &context, Type *elementType,
                                 std::size_t elementNum);
  // static PointerType *getFloatPtrType(Context& context);

private:
  TypeId typeId_;
};