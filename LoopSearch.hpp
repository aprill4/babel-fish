#pragma once

#include "IR.h"
#include "PassManager.h"
#include <map>
#include <set>
#include <vector>

struct CFGNode {
  std::set<CFGNode *> succs;
  std::set<CFGNode *> prevs;
  BasicBlock *bb;
  int index;   // the index of the node in CFG
  int lowlink; // the min index of the node in the strongly connected componets
  bool onStack;
};

class LoopSearch : public Pass {
public:
  explicit LoopSearch(Module *m, bool dump = false) : Pass(m), dump(dump) {}
  ~LoopSearch() = default;
  std::set<CFGNode *> build_cfg(Function *func);
  void run() override;
  bool strongly_connected_components(std::set<CFGNode *> &nodes,
                                     std::set<std::set<CFGNode *> *> &result);
  void dump_graph(std::set<CFGNode *> &nodes, std::string title);
  void traverse(CFGNode *n, std::set<std::set<CFGNode *> *> &result);
  CFGNode *find_loop_base(std::set<CFGNode *> *set,
                          std::set<CFGNode *> &reserved);

  // 利用iterator来遍历所有的loop
  auto begin() { return loop_set.begin(); }
  auto end() { return loop_set.end(); }

  BasicBlock *get_loop_base(std::set<BasicBlock *> *loop) {
    return loop2base[loop];
  }

  // 得到bb所在最低层次的loop
  std::set<BasicBlock *> *get_inner_loop(BasicBlock *bb) {
    if (bb2base.find(bb) == bb2base.end())
      return nullptr;
    return base2loop[bb2base[bb]];
  }

  // 得到输入loop的外一层的循环，如果没有则返回空
  std::set<BasicBlock *> *get_parent_loop(std::set<BasicBlock *> *loop);

  // 得到函数 f 里的所有循环
  std::set<std::set<BasicBlock *> *> get_loops_in_func(Function *f);

private:
  int index_count;
  bool dump;
  std::vector<CFGNode *> stack;
  // loops found
  std::set<std::set<BasicBlock *> *> loop_set;
  // loops found in a function
  std::map<Function *, std::set<std::set<BasicBlock *> *>> func2loop;
  // { entry bb of loop : loop }
  std::map<BasicBlock *, std::set<BasicBlock *> *> base2loop;
  // { loop : entry bb of loop }
  std::map<std::set<BasicBlock *> *, BasicBlock *> loop2base;
  // { bb :  entry bb of loop} 默认最低层次的loop
  std::map<BasicBlock *, BasicBlock *> bb2base;
};