#include "Function.h"
#include "BasicBlock.h"
#include "Types/FunctionType.h"
#include "Util.h"

Function::Function(const std::string &name, FunctionType *type, Module *parent)
    : Value(type, name), parent_(parent) {}

Module *Function::getModule() { return parent_; }

Type *Function::getReturnType() { return getFunctionType()->getReturnType(); }

std::size_t Function::getArgumentsNum() {
  return getFunctionType()->getArgumentsNum();
}

FunctionType *Function::getFunctionType() {
  return static_cast<FunctionType *>(getType());
}

void Function::addBasicBlock(BasicBlock *bb) { basicBlocks_.emplace_back(bb); }

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