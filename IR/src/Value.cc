#include "../include/Value.h"
#include "../include/Use.h"

Value::Value(Type *type, const std::string &name) : type_(type), name_(name) {}

Value::~Value() {}

bool Value::setName(const std::string &name) {
  if (name_ == "") {
    name_ = name;
    return true;
  }
  return false;
}

Type *Value::getType() { return type_; }

void Value::addUse(const Use &u) { useList_.emplace_front(u); }