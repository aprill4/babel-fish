#include "ConstantArray.h"

ConstantArray::ConstantArray(Context &c, ArrayType *type,
                             const std::vector<Constant *> &value)
    : Constant(c, type, "", 0), value_(value) {
  for (int i = 0; i < value.size(); i++) {
    setOperand(value_[i], i);
  }
}

ConstantArray *ConstantArray::get(Context &c, ArrayType *type,
                                  const std::vector<Constant *> &value) {
  return new ConstantArray(c, type, value);
}

Constant *ConstantArray::getElementValue(int idx) { return value_[idx]; }

std::string ConstantArray::print() {
  std::string const_ir;
  const_ir += getType()->getTypeName();
  const_ir += " ";
  const_ir += "[";
  for (int i = 0; i < value_.size(); i++) {
    const_ir += getElementValue(i)->print();
    const_ir += ", ";
  }
  return const_ir;
}