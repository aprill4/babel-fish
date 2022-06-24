#include "Instructions/StoreInst.h"
#include "BasicBlock.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"

// StoreInst::StoreInst(Value *val, Value *ptr, BasicBlock *bb)
//     : Instruction(Type::get_void_type(bb->get_module()), Instruction::store, 2, bb)
// {
//     set_operand(0, val);
//     set_operand(1, ptr);
// }


std::string StoreInst::print() {
  std::string IR;
  char IRtemp[30];
  // store <type> <value>, <type>* <pointer>
  std::string fmt("store %s %s, %s* %s");
  std::snprintf(
      IRtemp, sizeof IRtemp, fmt.c_str(), getOperandTypeName(0).c_str(),
      print_as_op(getOperand(0)).c_str(), getOperandTypeName(1).c_str(),
      print_as_op(getOperand(1)).c_str());
  IR.assign(IRtemp);
  return IR;
}