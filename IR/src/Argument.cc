#include "Argument.h"
#include "Function.h"

Argument::Argument(Type *type, const std::string &name, Function *func,
                   std::size_t argumentNo)
    : Value(type, name), parent_(func), argumentNo_(argumentNo) {}

std::string Argument::print() {
    return "";
}
