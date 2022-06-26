#include "GlobalVariable.h"
#include "Constant.h"
#include "Module.h"
#include "Util.h"

GlobalVariable::GlobalVariable(Type *type, const std::string &globalVarName,
                               bool isConst, Constant *initializer,
                               Module *insertedModule)
    : User(type, globalVarName, 1), initValue_(initializer) {
  setOperand(initializer, 0);
  insertedModule->addGlobalVariable(this);
}

GlobalVariable *GlobalVariable::Create(Type *type,
                                       const std::string &globalVarName,
                                       bool isConst, Constant *initializer,
                                       Module *insertedModule) {
  return new GlobalVariable(type, globalVarName, isConst, initializer,
                            insertedModule);
}
std::string GlobalVariable::print() {
  std::string global_val_ir;
  global_val_ir += print_as_op(this);
  global_val_ir += " = ";
  global_val_ir += (isConst_ ? "constant " : "global ");
  global_val_ir += getType()->getPtrElementType()->getTypeName();
  global_val_ir += " ";
  global_val_ir += initValue_->print();
  return global_val_ir;
}