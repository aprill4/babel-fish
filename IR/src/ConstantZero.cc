#include "ConstantZero.h"

ConstantZero *ConstantZero::get(Context &c, Type *type) { return new ConstantZero(c, type); }

std::string ConstantZero::print() { return "zeroinitializer"; }
