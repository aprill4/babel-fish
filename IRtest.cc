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
#include "Instructions/BranchInst.h"
#include "Instructions/IcmpInst.h"

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
  //int main(){
  //int a=1;
  //if(a>0) a++;
  //else a--;
  //int b=a;} 
  Context context;
  Module *m = new Module(context, "m");
  FunctionType *ft = FunctionType::get(Type::getInt1Type(context));
  Function *func = Function::Create(ft, "main", m);
  BasicBlock *bb = new BasicBlock(context, "bb", func);
  auto a_add = AllocaInst::Create(context, context.Int32Type, bb);
  StoreInst::Create(context, new ConstantInt(context.Int32Type, 1), a_add, bb);
  auto a = LoadInst::Create(context.Int32Type, a_add, bb);
  auto cond = IcmpInst::Create(context, IcmpInst::IcmpOp::GT, a, new ConstantInt(context.Int32Type, 1), bb);
  BasicBlock *bb1 = new BasicBlock(context, "bb1", func);
  BasicBlock *bb2 = new BasicBlock(context, "bb2", func);
  BasicBlock *bb3 = new BasicBlock(context, "bb3", func);
  bb->addSuccessor(bb1);
  bb->addSuccessor(bb2);
  bb1->addPredecessor(bb);
  bb1->addSuccessor(bb3);
  bb2->addPredecessor(bb);
  bb2->addSuccessor(bb3);
  BranchInst::Create(context, cond, bb1, bb2, bb);
  auto a_tmp = LoadInst::Create(context.Int32Type, a_add, bb1);
  auto a_1 = BinaryInst::CreateAdd(context, a_tmp, new ConstantInt(context.Int32Type, 1), bb1);
  StoreInst::Create(context, a, a_add, bb1);
  BranchInst::Create(context, bb3, bb1);
  a_tmp = LoadInst::Create(context.Int32Type, a_add, bb2); 
  auto a_2 = BinaryInst::CreateSub(context, a_tmp, new ConstantInt(context.Int32Type, 1), bb2);
  StoreInst::Create(context, a, a_add, bb2);
  BranchInst::Create(context, bb3, bb1);
  auto b_add = AllocaInst::Create(context, context.Int32Type, bb3);
  StoreInst::Create(context, a, b_add, bb3);
  ReturnInst::Create(context, new ConstantInt(context.Int32Type, 0), bb3);/**/
  cout << m->print() << endl;
  return 0;
}

/*
int main(){
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
}*/