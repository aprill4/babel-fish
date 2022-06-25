#include "Context.h"
#include "Type.h"
#include "Util.h"

Context::Context()
    : VoidType(new Type(Type::TypeId::VoidTypeId)),
      FloatType(new Type(Type::TypeId::FloatTypeId)),
      LabelType(new Type(Type::TypeId::LabelTypeId)),
      Int1Type(new IntegerType(1)), Int32Type(new IntegerType(32)) {}

Context::~Context() {
  delete VoidType;
  delete LabelType;
  delete FloatType;
  delete Int1Type;
  delete Int32Type;
  for (auto &ptr : PointerTypes) {
    delete ptr.second;
  }
  for (auto &arr : ArrayTypes) {
    delete arr.second;
  }
}

void Context::addModule(Module *module) { ownerModule = module; }

PointerType *Context::getPtrType(Type *ptrElementType) {
  if (PointerTypes.find(ptrElementType) == PointerTypes.end()) {
    PointerTypes[ptrElementType] = new PointerType(ptrElementType);
  }
  return PointerTypes[ptrElementType];
}

ArrayType *Context::getArrayType(Type *elementType, std::size_t elementNum) {
  if (ArrayTypes.find({elementType, elementNum}) == ArrayTypes.end()) {
    ArrayTypes[{elementType, elementNum}] =
        new ArrayType(elementType, elementNum);
  }
  return ArrayTypes[{elementType, elementNum}];
}
