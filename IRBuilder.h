#pragma once
#include "IR.h"
#include "LoopSearch.hpp"
#include "LoopInvHoist.hpp"
#include "Dominators.h"
#include "Mem2Reg.h"
#include "Gvn_Gcm.h"
#include <deque>

class Scope;
class Expression;
class IRBuilder {
public:
  IRBuilder()
      : context_(*new Context()), module_(new Module(context_, "main_module")),
        scope_(nullptr), basicblock_(nullptr) {
          init(context_);
        }

public:
  Module *getModule() { return module_; }
  Context &getContext() { return context_; }
  Scope *getScope() { return scope_; }
  BasicBlock *getBasicBlock() { return basicblock_; }
  BasicBlock *getWhileBlock() {
    return loop_.back().first;
  }
  BasicBlock *getNextBlock() {
    return loop_.back().second;
  }
  BasicBlock *getContinueBlock() {
    return while_loop_.back().first;
  }
  BasicBlock *getBreakBlock() {
    return while_loop_.back().second;
  }
  Expression *getCond() {
    return cond_.back();
  }
  Value *getTmpVal() { return val_; }
  Function *getFunction() { return func_; }

  void setScope(Scope *scope) { scope_ = scope; }
  void setBasicBlock(BasicBlock *basicblock) { basicblock_ = basicblock; }
  void setTmpVal(Value *val) { val_ = val; }
  void setFunction(Function *func) { func_ = func; }
  void setLoopBlock(BasicBlock *whileBlock, BasicBlock *nextBlock) {
    loop_.emplace_back(std::make_pair(whileBlock, nextBlock));
  }
  void setBreakAndContinue(BasicBlock *whileBlock, BasicBlock *nextBlock) {
    while_loop_.emplace_back(std::make_pair(whileBlock, nextBlock));
  }
  void setCond(Expression *cond) { cond_.emplace_back(cond); }
  void popLoopBlock() { loop_.pop_back(); }
  void popBreakAndContinueBlock() { while_loop_.pop_back(); }
  void popCond() { cond_.pop_back(); }
  std::size_t loopBlockSize() { return loop_.size(); }

private:
  Value *val_;
  Context &context_;
  Module *module_;
  Scope *scope_;
  BasicBlock *basicblock_;
  std::deque<std::pair<BasicBlock *, BasicBlock *>> loop_;
  std::deque<std::pair<BasicBlock *, BasicBlock *>> while_loop_;
  std::deque<Expression*> cond_;
  Function *func_;
};