#include "Instructions/BranchInst.h"
#include "BasicBlock.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"

// BranchInst::BranchInst(Value *cond, BasicBlock *if_true, BasicBlock
// *if_false,
//                        BasicBlock *bb)
//     : Instruction(Type::get_void_type(if_true->get_module()),
//     Instruction::br,
//                   3, bb) {
//   set_operand(0, cond);
//   set_operand(1, if_true);
//   set_operand(2, if_false);
// }

// BranchInst::BranchInst(BasicBlock *if_true, BasicBlock *bb)
//     : Instruction(Type::get_void_type(if_true->get_module()),
//     Instruction::br,
//                   1, bb) {
//   set_operand(0, if_true);
// }

bool BranchInst::isCondBr() { return getOperandNum() == 3; }

std::string BranchInst::print() {
  std::string IR;
  char IRtemp[30];
  if (isCondBr()) {
    // br i1 <cond>, label <iftrue>, label <iffalse>
    std::string fmt("br i1 %s, label %s, label %s");
    std::snprintf(
        IRtemp, sizeof IRtemp, fmt.c_str(), print_as_op(getOperand(0)).c_str(),
        print_as_op(getOperand(1)).c_str(), print_as_op(getOperand(2)).c_str());
  } else {
    // br label <dest>
    std::string fmt("br label %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(),
                  print_as_op(getOperand(0)).c_str());
  }
  IR.assign(IRtemp);
  return IR;
}
