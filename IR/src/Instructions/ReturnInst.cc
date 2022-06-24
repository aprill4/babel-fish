#include "../../include/Instructions/ReturnInst.h"
#include "../../include/BasicBlock.h"
#include "../../include/Types/Type.h"
#include "../../include/Util.h"
#include "../../include/Value.h"

// ReturnInst::ReturnInst(Value *val, BasicBlock *bb)
//     : Instruction(Type::get_void_type(bb->get_module()),
//     Instruction::OpId::ret, 1,
//                   bb) {
//   setOperand(val,0);
// }

// ReturnInst::ReturnInst(BasicBlock *bb)
//     : Instruction(Type::get_void_type(bb->get_module()), Instruction::ret, 0,
//                   bb) {}

bool ReturnInst::isVoidRet() { return getOperandNum() == 0; }

std::string ReturnInst::print() {
  std::string IR;
  char IRtemp[30];
  if (!isVoidRet()) {
    // ret <type> <value>
    std::string fmt("ret %s %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(),
                  getOperandTypeName(0).c_str(),
                  print_as_op(getOperand(0)).c_str());
  } else {
    // ret void
    return std::string("ret void");
  }
  IR.assign(IRtemp);
  return IR;
}
