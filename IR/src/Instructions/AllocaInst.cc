#include "../../include/Instructions/AllocaInst.h"
#include "../../include/BasicBlock.h"
#include "../../include/Types/Type.h"
#include "../../include/Util.h"
#include "../../include/Value.h"

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
