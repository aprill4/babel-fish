#include "Instructions/CallInst.h"
#include "BasicBlock.h"
#include "Function.h"
#include "Types/FunctionType.h"
#include "Util.h"
#include <cassert>

CallInst::CallInst(Context& c, Function *func, std::vector<Value *> funcArgs,
                   BasicBlock *insertedBlock, std::string name)
    : Instruction(c, func->getReturnType(), InstId::Call, funcArgs.size() + 1,
                  insertedBlock, name) {
  assert(func->getArgumentsNum() == funcArgs.size());
  setOperand(func, 0);
  for (int i = 0; i < funcArgs.size(); i++) {
    setOperand(funcArgs[i], i + 1);
  }
  insertedBlock->addInstruction(this);
}

CallInst *CallInst::Create(Context& c, Function *func, std::vector<Value *> funcArgs,
                           BasicBlock *insertedBlock, std::string name) {
  return new CallInst(c, func, funcArgs, insertedBlock, name);
}

FunctionType *CallInst::getFunctionType() {
  return static_cast<FunctionType *>(getOperand(0)->getType());
}

std::string CallInst::print() {
  std::string IR;
  char IRtemp[100];
  if (!isVoid()) {
    // <result> = call <return ty> <func name>(<function args>)
    std::string fmt("%%%s = call %s %s");
    std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
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
