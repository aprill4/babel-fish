#include "LoopSearch.hpp"
#include <fstream>
#include <unordered_set>

std::set<CFGNode *> LoopSearch::build_cfg(Function *func) {
  std::set<CFGNode *> result;
  std::map<BasicBlock *, CFGNode *> bb2cfg_node;
  for (auto bb : func->getBasicBlocks()) {
    auto node = new CFGNode;
    node->bb = bb;
    node->index = node->lowlink = -1;
    node->onStack = false;
    bb2cfg_node.insert({bb, node});
    result.insert(node);
  }
  for (auto bb : func->getBasicBlocks()) {
    auto node = bb2cfg_node[bb];
    std::string succ_string = bb->getLLVM_Name() + " success node: ";
    for (auto succ : bb->getSuccessor()) {
      succ_string = succ_string + succ->getLLVM_Name() + " ";
      node->succs.insert(bb2cfg_node[succ]);
    }
    // std::cout << succ_string << std::endl;
    std::string prev_string = bb->getLLVM_Name() + " previous node: ";
    for (auto prev : bb->getPredecessors()) {
      prev_string = prev_string + prev->getLLVM_Name() + " ";
      node->prevs.insert(bb2cfg_node[prev]);
    }
    // std::cout << prev_string << std::endl;
  }
  return result;
}

// Tarjan algorithm
// reference:
// https://baike.baidu.com/item/tarjan%E7%AE%97%E6%B3%95/10687825?fr=aladdin
bool LoopSearch::strongly_connected_components(
    std::set<CFGNode *> &nodes, std::set<std::set<CFGNode *> *> &result) {
  index_count = 0;
  stack.clear();
  for (auto n : nodes) {
    if (n->index == -1)
      traverse(n, result);
  }
  return result.size() != 0;
}

void LoopSearch::traverse(CFGNode *n, std::set<std::set<CFGNode *> *> &result) {
  n->index = index_count++;
  n->lowlink = n->index;
  stack.push_back(n);
  n->onStack = true;

  for (auto su : n->succs) {
    // has not visited su
    if (su->index == -1) {
      traverse(su, result);
      n->lowlink = std::min(su->lowlink, n->lowlink);
    }
    // has visited su
    else if (su->onStack) {
      n->lowlink = std::min(su->index, n->lowlink);
    }
  }

  // nodes that in the same strongly connected component will be popped out of
  // stack
  if (n->index == n->lowlink) {
    auto set = new std::set<CFGNode *>;
    CFGNode *tmp;
    do {
      tmp = stack.back();
      tmp->onStack = false;
      set->insert(tmp);
      stack.pop_back();
    } while (tmp != n);
    if (set->size() == 1)
      delete set;
    else
      result.insert(set);
  }
}

CFGNode *LoopSearch::find_loop_base(std::set<CFGNode *> *set,
                                    std::set<CFGNode *> &reserved) {
  CFGNode *base = nullptr;
  bool hadBeen = false;
  for (auto n : *set) {
    for (auto prev : n->prevs) {
      if (set->find(prev) == set->end()) {
        base = n;
      }
    }
  }
  if (base != nullptr)
    return base;
  for (auto res : reserved) {
    for (auto succ : res->succs) {
      if (set->find(succ) != set->end()) {
        base = succ;
      }
    }
  }
  return base;
}

void LoopSearch::run() {
  auto func_list = m_->functionList_;
  for (auto func : func_list) {
    if (func->getBasicBlocks().size() == 0) {
      continue;
    } else {
      std::set<CFGNode *> nodes;
      std::set<CFGNode *> reserved;
      std::set<std::set<CFGNode *> *> sccs;

      // step 1: build cfg
      nodes = build_cfg(func);
      // dump graph
      dump = true;
      dump_graph(nodes, func->getName());
      // step 2: find strongly connected graph from external to internal
      int scc_index = 0;
      while (strongly_connected_components(nodes, sccs)) {
        if (sccs.size() == 0) {
          break;
        } else {
          // step 3: find loop base node for each strongly connected graph
          for (auto scc : sccs) {
            scc_index += 1;
            auto base = find_loop_base(scc, reserved);
            // step 4: store result
            auto bb_set = new std::set<BasicBlock *>;
            std::string node_set_string = "";
            for (auto n : *scc) {
              bb_set->insert(n->bb);
              node_set_string = node_set_string + n->bb->getLLVM_Name() + ',';
            }
            loop_set.insert(bb_set);
            func2loop[func].insert(bb_set);
            base2loop.insert({base->bb, bb_set});
            loop2base.insert({bb_set, base->bb});
            for (auto bb : *bb_set) {
              if (bb2base.find(bb) == bb2base.end()) {
                bb2base.insert({bb, base->bb});
              } else {
                bb2base[bb] = base->bb;
              }
            }
            // step 5: map each node to loop base
            for (auto bb : *bb_set) {
              if (bb2base.find(bb) == bb2base.end())
                bb2base.insert({bb, base->bb});
              else
                bb2base[bb] = base->bb;
            }
            // step 6: remove loop base node for researching inner loop
            reserved.insert(base);
            dump_graph(*scc, func->getName() + '_' + std::to_string(scc_index));
            nodes.erase(base);
            for (auto su : base->succs) {
              su->prevs.erase(base);
            }
            for (auto prev : base->prevs) {
              prev->succs.erase(base);
            }
          }
          for (auto scc : sccs)
            delete scc;
          sccs.clear();
          for (auto n : nodes) {
            n->index = n->lowlink = -1;
            n->onStack = false;
          }
        }
      }
      reserved.clear();
      for (auto node : nodes) {
        delete node;
      }
      nodes.clear();
    }
  }
}

void LoopSearch::dump_graph(std::set<CFGNode *> &nodes, std::string title) {
  if (dump) {
    std::vector<std::string> edge_set;
    for (auto node : nodes) {
      if (node->bb->getLLVM_Name() == "") {
        return;
      }
      if (base2loop.find(node->bb) != base2loop.end()) {
        for (auto succ : node->succs) {
          if (nodes.find(succ) != nodes.end()) {
            edge_set.insert(edge_set.begin(),
                            '\t' + node->bb->getLLVM_Name() + "->" +
                                succ->bb->getLLVM_Name() + ';' + '\n');
          }
        }
        edge_set.insert(edge_set.begin(), '\t' + node->bb->getLLVM_Name() +
                                              " [color=red]" + ';' + '\n');
      } else {
        for (auto succ : node->succs) {
          if (nodes.find(succ) != nodes.end()) {
            edge_set.push_back('\t' + node->bb->getLLVM_Name() + "->" +
                               succ->bb->getLLVM_Name() + ';' + '\n');
          }
        }
      }
    }
    std::string digragh = "digraph G {\n";
    for (auto edge : edge_set) {
      digragh += edge;
    }
    digragh += '}';
    std::ofstream file_output;
    file_output.open(title + ".dot", std::ios::out);

    file_output << digragh;
    file_output.close();
    std::string dot_cmd =
        "dot -Tpng " + title + ".dot" + " -o " + title + ".png";
    std::system(dot_cmd.c_str());
  }
}

std::set<BasicBlock *> *
LoopSearch::get_parent_loop(std::set<BasicBlock *> *loop) {
  auto base = loop2base[loop];
  for (auto prev : base->getPredecessors()) {
    if (loop->find(prev) != loop->end())
      continue;
    auto loop = get_inner_loop(prev);
    if (loop == nullptr || loop->find(base) == loop->end())
      return nullptr;
    else {
      return loop;
    }
  }
  return nullptr;
}

std::set<std::set<BasicBlock *> *> LoopSearch::get_loops_in_func(Function *f) {
  return func2loop.count(f) ? func2loop[f]
                            : std::set<std::set<BasicBlock *> *>();
}
