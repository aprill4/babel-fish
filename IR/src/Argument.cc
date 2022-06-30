#include "Argument.h"
#include "Function.h"

Argument::Argument(Context &c, Type *type, const std::string &name, Function *func,
                   std::size_t argumentNo)
    : Value(c, type, name), parent_(func), argumentNo_(argumentNo) {}

std::string Argument::print() {
   return getLLVM_Name(); 
}
