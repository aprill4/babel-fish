#include "ConstantZero.h"

ConstantZero *ConstantZero::get(Type *type) { return new ConstantZero(type); }

std::string ConstantZero::print() { return "zeroinitializer"; }
