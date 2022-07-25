#include "ConstantArray.h"
#include "Exception.h"

ConstantArray::ConstantArray(Context &c, ArrayType *type,
                             const std::vector<Value *> &value,
                             const std::vector<int> &dimension)
    : Constant(c, type, "", value.size()), value_(value), dimension_(dimension) {
  for (int i = 0; i < value.size(); i++) {
    setOperand(value_[i], i);
  }
}

ConstantArray *ConstantArray::get(Context &c, ArrayType *type,
                                  const std::vector<Value *> &value, const std::vector<int> &dimension) {
  return new ConstantArray(c, type, value, dimension);
}

Value *ConstantArray::getElementValue(int idx) { 
  if (idx >= value_.size()) {
    throw Exception("out of array bound");
  }
  return value_[idx]; 
}

std::string ConstantArray::print() {
  std::string const_ir;
  const_ir += getType()->getTypeName();
  const_ir += " ";
  const_ir += "[";
  for (int i = 0; i < value_.size(); i++) {
    const_ir += getElementValue(i)->print();
    const_ir += ", ";
  }
  const_ir += "]";
  return const_ir;
}