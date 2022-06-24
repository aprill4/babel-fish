#include "Instructions/CallInst.h"
#include "Function.h"
#include "Types/FunctionType.h"
#include "Util.h"
#include <cassert>

CallInst::CallInst(Function *func, std::vector<Value *> args, BasicBlock *bb)
    : Instruction(func->getReturnType(), Instruction::OpId::call,
                  args.size() + 1, bb) {
  assert(func->getArgumentsNum() == args.size());
  int operandNum = args.size() + 1;
  setOperand(func, 0);
  for (int i = 1; i < operandNum; i++) {
    setOperand(args[i - 1], i);
  }
}

FunctionType *CallInst::getFunctionType() {
  return static_cast<FunctionType *>(getOperand(0)->getType());
}

std::string CallInst::print() {
  std::string IR;
  char IRtemp[30];
  if (!isVoid()) {
    // <result> = call <return ty> <func name>(<function args>)
    std::string fmt("%%%s = call %s %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getName().c_str(),
                  getType()->getTypeName().c_str(),
                  print_as_op(getOperand(0)).c_str());
  } else {
    // call <return ty> <func name>(<function args>)
    std::string fmt("call %s %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(),
                  getType()->getTypeName().c_str(),
                  print_as_op(getOperand(0)).c_str());
  }
  IR.assign(IRtemp);
  IR += "(";
  for (int i = 1; i < getOperandNum(); i++) {
    if (i > 1)
      IR += ", ";
    IR += this->getOperand(i)->getType()->getTypeName() + " " +
          print_as_op(getOperand(i));
  }
  IR += ")";
  return IR;
}
