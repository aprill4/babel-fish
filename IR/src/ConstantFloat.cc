#include "ConstantFloat.h"
#include "Context.h"

ConstantFloat *ConstantFloat::get(Context &context, double value) {
  return new ConstantFloat(context, Type::getFloatType(context), value);
}

std::string ConstantFloat::print() {
  std::string fp_ir;
  char dstr[20];
  snprintf(dstr, 20, "%.8lf", value_);
  fp_ir.assign(dstr);
  return fp_ir;
}