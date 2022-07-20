#include "Function.h"
#include "Argument.h"
#include "BasicBlock.h"
#include "Module.h"
#include "Types/FunctionType.h"
#include "Util.h"
#include <cassert>

Function::Function(Context &c, FunctionType *funcType, const std::string args_name[], const std::string &funcName,
                   Module *parent)
    : Value(funcType, funcName), parent_(parent) {
  assert(parent != nullptr);
  parent_->addFuntion(this);
  for (int i = 0; i < getArgumentsNum(); i++) {
    arguments_.emplace_back(
        new Argument(c, funcType->getArgumentType(i), args_name[i], this, i));
  }
}

Function *Function::Create(Context &c, FunctionType *funcType, const std::string args_name[], const std::string &funcName,
                           Module *parent) {
  assert(parent != nullptr);
  return new Function(c ,funcType, args_name, funcName, parent);
}

Module *Function::getModule() { return parent_; }

Type *Function::getReturnType() { return getFunctionType()->getReturnType(); }

std::size_t Function::getArgumentsNum() {
  return getFunctionType()->getArgumentsNum();
}

FunctionType *Function::getFunctionType() {
  return static_cast<FunctionType *>(getType());
}

void Function::addBasicBlock(BasicBlock *bb) { basicBlocks_.emplace_back(bb); }

void Function::remove(BasicBlock* bb){
  basicBlocks_.remove(bb);
}


Argument *Function::getArgument(size_t idx) { 
  assert(idx < getArgumentsNum() && "argument idx is out of range");
  return arguments_[idx];
}

std::string Function::print() {
  std::string func_ir;
  // set_instr_name();
  // if (this->is_declaration()) {
  //   func_ir += "declare ";
  // } else {
  func_ir += "define ";
  // }

  func_ir += getReturnType()->getTypeName();
  func_ir += " ";
  func_ir += print_as_op(this);
  func_ir += "(";

  int args_num = getArgumentsNum();
  for (int i = 0; i < args_num; i++){
    auto arg = arguments_[i];
    func_ir += arg->getType()->getTypeName();
    func_ir += " ";
    func_ir += arg->print();

    if (args_num-1 > i){
      func_ir += ", ";
    }
  }

  func_ir += ")";
  // // print arg
  // if (this->is_declaration()) {
  //   for (int i = 0; i < this->get_num_of_args(); i++) {
  //     if (i)
  //       func_ir += ", ";
  //     func_ir += static_cast<FunctionType *>(this->get_type())
  //                    ->get_param_type(i)
  //                    ->print();
  //   }
  // } else {
  //   for (auto arg = this->arg_begin(); arg != arg_end(); arg++) {
  //     if (arg != this->arg_begin()) {
  //       func_ir += ", ";
  //     }
  //     func_ir += static_cast<Argument *>(*arg)->print();
  //   }
  // }
  // func_ir += ")";

  // print bb
  // if (this->is_declaration()) {
  //   func_ir += "\n";
  // } else {
  func_ir += " {";
  func_ir += "\n";
  for (auto bb : basicBlocks_) {
    func_ir += bb->print();
  }
  func_ir += "}";
  // }
  // std::cout << func_ir << std::endl;
  return func_ir;
}