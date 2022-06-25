#include "BasicBlock.h"
#include "ConstantInt.h"
#include "Context.h"
#include "Function.h"
#include "Instructions/AllocaInst.h"
#include "Instructions/GetElementPtrInst.h"
#include "Instructions/ReturnInst.h"
#include "Module.h"
#include "Types/ArrayType.h"
#include "Types/FunctionType.h"
#include "Types/IntegerType.h"
#include <iostream>
using namespace std;

Module *yy() {
  Context * c = new Context();
  Module *m = new Module(*c, "m");
  FunctionType *ft = FunctionType::get(Type::getInt1Type(*c));
  Function *func = Function::Create(ft, "main", m);
  BasicBlock *bb = new BasicBlock(*c, "bb2", func);
  ConstantInt *val = new ConstantInt(Type::getInt32Type(*c), 0);
  ReturnInst::Create(*c, val, bb);
  ArrayType *i32_arr10_t = ArrayType::get(*c, Type::getInt32Type(*c), 10);
  auto alloca = AllocaInst::Create(*c, i32_arr10_t, bb);
  GetElementPtrInst::Create(*c, alloca,
                            {new ConstantInt(Type::getInt32Type(*c), 0),
                             new ConstantInt(Type::getInt32Type(*c), 0)},
                            bb);
  // ReturnInst *ret = new ReturnInst(c, val, bb);
  return m;
}

int main() {
  // auto a = yy();
  // auto x = a->print();
  // std::cout << x;
  Context c;
  cout << &c << endl;
  Module *m = new Module(c, "m");
  FunctionType *ft = FunctionType::get(Type::getInt1Type(c));
  Function *func = Function::Create(ft, "main", m);
  BasicBlock *bb = new BasicBlock(c, "bb2", func);
  ConstantInt *val = new ConstantInt(Type::getInt32Type(c), 0);
  ReturnInst::Create(c, val, bb);
  ArrayType *i32_arr10_t = ArrayType::get(c, Type::getInt32Type(c), 10);
  auto a = AllocaInst::Create(c, i32_arr10_t, bb);
  GetElementPtrInst::Create(c, a,
                            {new ConstantInt(Type::getInt32Type(c), 0),
                             new ConstantInt(Type::getInt32Type(c), 0)},
                            bb);
  cout << m->print() << endl;
  return 0;
}