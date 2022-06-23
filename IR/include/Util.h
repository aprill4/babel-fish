#pragma once

#include "Constant.h"
#include "Function.h"
#include "GlobalVariable.h"
#include "Types/Type.h"
#include "Value.h"
#include <string>

inline std::string print_as_op(Value *v) {
  std::string op_ir;
  if (dynamic_cast<GlobalVariable *>(v)) {
    op_ir += "@" + v->getName();
  } else if (dynamic_cast<Function *>(v)) {
    op_ir += "@" + v->getName();
  } else if (dynamic_cast<Constant *>(v)) {
    op_ir += v->print();
  } else {
    op_ir += "%" + v->getName();
  }
  return op_ir;
}
