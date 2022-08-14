#include "LoopInvHoist.hpp"
#include "LoopSearch.hpp"
#include <algorithm>

void LoopInvHoist::run() {
  // 先通过LoopSearch获取循环的相关信息
  LoopSearch loop_searcher(m_, false);
  loop_searcher.run();

  // 接下来由你来补充啦！
  int change_flag = 0;
  for (auto f : m_->functionList_) {
    for (auto loop : loop_searcher.get_loops_in_func(f)) {
      change_flag = 1;
      std::set<Value *> change_var;
      std::vector<Instruction *> delete_instr;
      for (auto bb : *loop) {
        for (auto instr : bb->instructionList_) {
          if (instr->isBinary() || instr->isIcmp() || instr->isFcmp() ||
              instr->isCall() || instr->isFp2si() || instr->isSi2fp() ||
              instr->isZext())
            change_var.insert(instr);
          if (instr->isPhi())
            change_var.insert(instr);
        }
      }
      //首先将一个循环中所有被赋值的左值加入，这样用来找到没被改变的
      while (change_flag == 1) {
        change_flag = 0;
        for (auto bb : *loop) {
          for (auto instr : bb->instructionList_) { //对于循环中的每一条指令
            if (instr->isBinary() || instr->isIcmp() ||
                instr
                    ->isFcmp()) { //如果是一条运算，且操作数都不在change里，外提
              auto op0 = instr->getOperand(0);
              auto op1 = instr->getOperand(1);
              bool iop0 = (change_var.find(op0) == change_var.end());
              bool iop1 = (change_var.find(op1) == change_var.end());
              bool varfind = (change_var.find(instr) != change_var.end());
              if (iop0 && iop1 && varfind) {
                change_flag = 1;
                delete_instr.emplace_back(instr);
                change_var.erase(instr);
              }
            }
            if (instr->isZext() || instr->isFp2si() ||
                instr
                    ->isSi2fp()) { //如果是一条运算，且操作数都不在change里，外提
              auto op0 = instr->getOperand(0);
              bool iop0 = (change_var.find(op0) == change_var.end());
              bool varfind = (change_var.find(instr) != change_var.end());
              if (iop0 && varfind) {
                change_flag = 1;
                delete_instr.emplace_back(instr);
                change_var.erase(instr);
              }
            }
            if (instr->isCall()) {
              bool needdel = 1;
              for (auto op : instr->operands_) {
                if (change_var.find(op) != change_var.end()) {
                  needdel = 0;
                  break;
                }
              }
              bool varfind = (change_var.find(instr) != change_var.end());
              if (needdel && varfind) {
                change_flag = 1;
                delete_instr.emplace_back(instr);
                change_var.erase(instr);
              }
            }
          }
        }
      }
      auto base = loop_searcher.get_loop_base(loop);
      BasicBlock *preBB;
      for (auto pre : base->getPredecessors()) {
        if ((*loop).find(pre) == (*loop).end()) {
          preBB = pre;
          break;
        }
      }
      BasicBlock *homeBB;
      // Instruction* instr;
      Instruction *term;
      term = preBB->instructionList_.back();
      preBB->instructionList_.pop_back();
      for (auto instr : delete_instr) {
        // instr=delete_instr.back();
        // delete_instr.pop_back();
        preBB->addInstruction(instr);
        for (auto bb : (*loop)) {
          for (auto homeinstr : bb->instructionList_) {
            if (homeinstr == instr)
              homeBB = bb;
          }
        }
        homeBB->instructionList_.remove(instr);
      }
      preBB->instructionList_.emplace_back(term);
      delete_instr.clear();
      change_var.clear();
    }
  }
}