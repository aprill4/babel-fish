#pragma once

#include "Constant.h"
#include "Function.h"
#include "GlobalVariable.h"
#include "Types/Type.h"
#include "Value.h"
#include <string>
#include <iostream>

inline std::string print_as_op(Value *v) {
  std::string op_ir;
  if (dynamic_cast<GlobalVariable *>(v)) {
    op_ir += "@" + v->getLLVM_Name();
  } else if (dynamic_cast<Function *>(v)) {
    op_ir += "@" + v->getName();
  } else if (dynamic_cast<Constant *>(v)) {
    op_ir += v->print();
  } else {
    op_ir += "%" + v->getLLVM_Name();
  }
  return op_ir;
}
