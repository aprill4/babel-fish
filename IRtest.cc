#include "BasicBlock.h"
#include "ConstantInt.h"
#include "Context.h"
#include "Function.h"
#include "Instructions/ReturnInst.h"
#include "Module.h"
#include "Types/FunctionType.h"
#include "Types/IntegerType.h"
#include <iostream>
using namespace std;

Module *yy() {
  Context c;
  cout << &c << endl;
  Module *m = new Module(c, "m");
  FunctionType *ft = FunctionType::get(Type::getInt1Type(c));
  Function *func = Function::Create(ft, "main", m);
  BasicBlock *bb = new BasicBlock(c, "bb2", func);
  ConstantInt *val = new ConstantInt(Type::getInt32Type(c), 0);
  ReturnInst::Create(c,val,bb);
  // ReturnInst *ret = new ReturnInst(c, val, bb);
  return m;
}

int main() {
  auto a = yy();
  auto x = a->print();
  std::cout << x;
  return 0;
}