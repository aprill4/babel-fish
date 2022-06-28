#include "Module.h"
#include "BasicBlock.h"
#include "ConstantInt.h"
#include "Context.h"
#include "Function.h"
#include "Argument.h"

#include "Instructions/AllocaInst.h"
#include "Instructions/GetElementPtrInst.h"
#include "Instructions/ReturnInst.h"
#include "Instructions/StoreInst.h"
#include "Instructions/LoadInst.h"
#include "Instructions/BinaryInst.h"

#include "Types/ArrayType.h"
#include "Types/FunctionType.h"
#include "Types/IntegerType.h"

#include <iostream>
using namespace std;
/*
Module *yy() {
  Context *c = new Context();
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
*/
int main() {
  // auto a = yy();
  // auto x = a->print();
  // std::cout << x;
  /*
  Context c;
  Module *m = new Module(c, "m");
  FunctionType *ft = FunctionType::get(Type::getInt1Type(c));
  Function *func = Function::Create(ft, "main", m);
  BasicBlock *bb = new BasicBlock(c, "bb2", func);
  ConstantInt *val = new ConstantInt(Type::getInt32Type(c), 0);
  ReturnInst::Create(c, val, bb);
  ArrayType *i32_arr10_t = ArrayType::get(c, Type::getInt32Type(c), 10);
  auto a = AllocaInst::Create(c, i32_arr10_t, bb);
  cout << a->getAllocaType()->getTypeName() << endl;
  auto a_0 =
      GetElementPtrInst::Create(c, a,
                                {new ConstantInt(Type::getInt32Type(c), 0),
                                 new ConstantInt(Type::getInt32Type(c), 0)},
                                bb);
  StoreInst::Create(c, new ConstantInt(Type::getInt32Type(c), 0), a_0, bb);
  cout << m->print() << endl;
  return 0;
  */

  Context c;
  Module *m = new Module(c, "m");

  vector<Type *> args_t = {Type::getInt32Type(c), Type::getInt32Type(c)};
  FunctionType *ft = FunctionType::get(Type::getFloatType(c), args_t);
  Function *func = Function::Create(ft, "mul", m);

  vector<Argument *> args;
  int i = 0;
  for (auto arg_t: args_t){
    string name = "arg";
    char no = '0' + i;
    Argument *a = new Argument(arg_t, name + no, func, i);
    args.emplace_back(a);
    i++;
  }

  BasicBlock *bb = new BasicBlock(c, "mul", func);

  auto a1 = AllocaInst::Create(c, Type::getInt32Type(c), bb);
  auto a2 = AllocaInst::Create(c, Type::getInt32Type(c), bb);

  StoreInst::Create(c, args[0], a1, bb);
  StoreInst::Create(c, args[1], a2, bb);

  auto l1 = LoadInst::Create(a1->getAllocaType(), a1, bb);
  auto l2 = LoadInst::Create(a2->getAllocaType(), a2, bb);

  BinaryInst::CreateMul(c, l1, l2, bb);

  cout << m->print() << endl;
  return 0;
}