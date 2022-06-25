#include "ConstantInt.h"
#include "Types/IntegerType.h"
#include "Util.h"

std::string ConstantInt::print() {
  std::string const_ir;
  Type *ty = getType();
  if (ty->isIntegerType() &&
      static_cast<IntegerType *>(ty)->getBitsNum() == 1) {
    // int1
    const_ir += (getValue() == 0) ? "false" : "true";
  } else {
    // int32
    const_ir += std::to_string(getValue());
  }
  return const_ir;
}