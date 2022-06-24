#include "ConstantInt.h"
#include "Util.h"
#include "Types/IntegerType.h"

std::string ConstantInt::print() {
  std::string const_ir;
  Type *ty = getType();
  if (ty->isIntegerType() &&
      static_cast<IntegerType *>(ty)->getBitsNum() == 1) {
    // int1
    const_ir += (this->getValue() == 0) ? "false" : "true";
  } else {
    // int32
    const_ir += std::to_string(this->getValue());
  }
  return const_ir;
}