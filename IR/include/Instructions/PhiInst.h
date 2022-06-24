#pragma once

#include "Instruction.h"

class PhiInst : public Instruction {
public:
  PhiInst(OpId op, std::vector<Value *> vals, std::vector<BasicBlock *> val_bbs,
          Type *ty, BasicBlock *bb);
  PhiInst(Type *ty, OpId op, unsigned num_ops, BasicBlock *bb)
      : Instruction(ty, op, num_ops, bb) {}
  //   static PhiInst *create_phi(Type *ty, BasicBlock *bb);
  //   Value *get_lval() { return l_val_; }
  //   void set_lval(Value *l_val) { l_val_ = l_val; }
  //   void add_phi_pair_operand(Value *val, Value *pre_bb) {
  //     this->addOperand(val);
  //     this->addOperand(pre_bb);
  //   }
  std::string print() override;

private:
  Value *l_val_;
};