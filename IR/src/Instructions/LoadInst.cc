#include "../../include/Instructions/LoadInst.h"
#include "../../include/BasicBlock.h"
#include "../../include/Types/PointerType.h"
#include "../../include/Types/Type.h"
#include "../../include/Util.h"
#include "../../include/Value.h"
#include <cassert>



std::string LoadInst::print() {
  std::string IR;
  char IRtemp[30];
  // <result> = load <type>, <type>* <pointer>
  std::string fmt("%%%s = load %s, %s* %s");
  assert(getOperandType(0)->isPointerType());
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getName().c_str(),
                getOperandType(0)->getPtrElementType()->getTypeName().c_str(),
                getOperandTypeName(0).c_str(),
                print_as_op(getOperand(0)).c_str());
  IR.assign(IRtemp);
  return IR;
}