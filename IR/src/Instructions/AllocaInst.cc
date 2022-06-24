#include "Instructions/AllocaInst.h"
#include "BasicBlock.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"

Type *AllocaInst::getAllocaType() { return allocaType_; }

std::string AllocaInst::print() {
  std::string IR;
  char IRtemp[30];
  // <result> = alloca <type>
  std::string fmt("%%%s = alloca %s");
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getName().c_str(),
                allocaType_->getTypeName().c_str());
  IR.assign(IRtemp);
  return IR;
}
