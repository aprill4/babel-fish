#include "Value.h"
#include "Use.h"
#include <iostream>

Value::Value(Type *type, const std::string &name) : type_(type), name_(name) {}

Value::Value(Context &c, Type *type, const std::string &name) : type_(type), name_(name), no_(c.counter++) {}

bool Value::setName(const std::string &name) {
  if (name_ == "") {
    name_ = name;
    return true;
  }
  return false;
}

std::string Value::getName() { return name_; }

std::string Value::getLLVM_Name() { 
  return name_ + std::to_string(no_); }

Type *Value::getType() { return type_; }

size_t Value::getNO() { return no_; }

void Value::addUse(const Use &u) { useList_.emplace_front(u); }