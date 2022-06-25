#include "Value.h"
#include "Use.h"

Value::Value(Type *type, const std::string &name) : type_(type), name_(name) {}

bool Value::setName(const std::string &name) {
  if (name_ == "") {
    name_ = name;
    return true;
  }
  return false;
}

std::string Value::getName() { return name_; }

Type *Value::getType() { return type_; }

void Value::addUse(const Use &u) { useList_.emplace_front(u); }