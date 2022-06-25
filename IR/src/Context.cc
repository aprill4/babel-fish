#include "Context.h"
#include "Type.h"
#include "Util.h"

Context::Context()
    : VoidType(Type::TypeId::VoidTypeId), FloatType(Type::TypeId::FloatTypeId),
      LabelType(Type::TypeId::LabelTypeId), Int1Type(1), Int32Type(32) {}

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
