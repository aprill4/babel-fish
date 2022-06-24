#include "Function.h"
#include "Types/FunctionType.h"

Function::Function(const std::string &name, FunctionType *type, Module *parent)
    : Value(type, name), parent_(parent) {}

Module *Function::getParent() { return parent_; }

Type *Function::getReturnType() { return getFunctionType()->getReturnType(); }

std::size_t Function::getArgumentsNum() {
  return getFunctionType()->getArgumentsNum();
}

FunctionType *Function::getFunctionType() {
  return static_cast<FunctionType *>(getType());
}

std::string Function::print(){
    return "";
}