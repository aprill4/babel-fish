#include "Instructions/GetElementPtrInst.h"
#include "BasicBlock.h"
#include "Types/PointerType.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"
#include <cassert>

Type *GetElementPtrInst::getElementType() { return elementType_; }

std::string GetElementPtrInst::print() {
  std::string IR;
  char IRtemp[30];
  // <result> = getelementptr <type>, <type>* <ptrval> [, <type> <idx>]
  std::string fmt("%%%s = getelementptr %s, ");
  assert(getOperandType(0)->isPointerType());
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getName().c_str(),
                getOperandType(0)->getPtrElementType()->getTypeName().c_str());
  IR.assign(IRtemp);
  for (int i = 0; i < getOperandNum(); i++) {
    if (i > 0)
      IR += ", ";
    IR += getOperand(i)->getType()->getTypeName() + " " +
          print_as_op(getOperand(i));
  }
  return IR;
}
