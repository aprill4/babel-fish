#pragma once

#include "ArrayType.h"
#include "PointerType.h"
#include "Types/IntegerType.h"
#include "Types/Type.h"
#include <map>

class Module;

class Context {
public:
  Context();
  ~Context();
  Module *ownerModule;
  Type *VoidType, *LabelType, *FloatType;
  IntegerType *Int1Type, *Int32Type;
  std::map<std::pair<Type *, std::size_t>, ArrayType *> ArrayTypes;
  std::map<Type *, PointerType *> PointerTypes;
  void addModule(Module *module);
  PointerType *getPtrType(Type *ptrElementType);
  ArrayType *getArrayType(Type *elementType, std::size_t elementNum);

private:
};
