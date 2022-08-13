#include "IRBuilder.h"

#define IS_GLOBAL_VARIABLE(l_val) dynamic_cast<GlobalVariable *>(l_val)
#define IS_GEP_INSTR(l_val) dynamic_cast<GetElementPtrInst *>(l_val)

std::map<Value *, std::vector<Value *>> var_val_stack;

void Mem2Reg::run() {
  // get info from Dominators
  dominators_ = new Dominators(m_);
  dominators_->run();
  for (auto f : m_->functionList_) {
    func_ = f;
    if (func_->getBasicBlocks().size() >= 1) {
      generate_phi();
      re_name(func_->getEntryBlock());
    }
    remove_alloca();
  }
}

void Mem2Reg::generate_phi() {
  // step 1: find all global_live_var_name x and get their blocks
  std::set<Value *> global_live_var_name;
  std::map<Value *, std::set<BasicBlock *>> live_var_2blocks;
  for (auto bb : func_->basicBlocks_) {
    std::set<Value *> var_is_killed;
    for (auto instr : bb->instructionList_) {
      if (instr->isStore()) {
        // store i32 a, i32 *b
        // a is r_val, b is l_val
        auto r_val = static_cast<StoreInst *>(instr)->getRval();
        auto l_val = static_cast<StoreInst *>(instr)->getLval();

        if (!dynamic_cast<GlobalVariable *>(l_val) &&
            !dynamic_cast<GetElementPtrInst *>(l_val)) {
          if (var_is_killed.find(r_val) == var_is_killed.end()) {
            global_live_var_name.insert(l_val);
          }
          var_is_killed.insert(l_val);
          live_var_2blocks[l_val].insert(bb);
        }
      }
    }
  }
  // step 2: insert phi instr
  std::map<std::pair<BasicBlock *, Value *>, bool>
      bb_has_var_phi; // bb has phi for var
  for (auto var : global_live_var_name) {
    std::vector<BasicBlock *> work_list(live_var_2blocks[var].begin(),
                                        live_var_2blocks[var].end());
    for (int i = 0; i < work_list.size(); i++) {
      auto bb = work_list[i];
      for (auto bb_dominance_frontier_bb :
           dominators_->get_dominance_frontier(bb)) {
        if (bb_has_var_phi.find({bb_dominance_frontier_bb, var}) ==
            bb_has_var_phi.end()) {
          // generate phi for bb_dominance_frontier_bb & add
          // bb_dominance_frontier_bb to work list
          auto phi =
              PhiInst::Create(m_->context_, var->getType()->getPtrElementType(),
                              bb_dominance_frontier_bb);
          phi->setLval(var);
          bb_dominance_frontier_bb->addInstInBegin(phi);
          work_list.emplace_back(bb_dominance_frontier_bb);
          bb_has_var_phi[{bb_dominance_frontier_bb, var}] = true;
        }
      }
    }
  }
}

void Mem2Reg::re_name(BasicBlock *bb) {
  std::vector<Instruction *> wait_delete;
  for (auto instr : bb->instructionList_) {
    if (instr->isPhi()) {
      // step 3: push phi instr as lval's lastest value define
      auto l_val = static_cast<PhiInst *>(instr)->getLval();
      var_val_stack[l_val].emplace_back(instr);
    }
  }

  for (auto instr : bb->instructionList_) {
    if (instr->isLoad()) {
      // step 4: replace load with the top of stack[l_val]
      auto l_val = static_cast<LoadInst *>(instr)->getLval();
      if (!IS_GLOBAL_VARIABLE(l_val) && !IS_GEP_INSTR(l_val)) {
        if (var_val_stack.find(l_val) != var_val_stack.end()) {
          instr->replaceAllUseWith(var_val_stack[l_val].back());
          wait_delete.emplace_back(instr);
        }
      }
    }
    if (instr->isStore()) {
      // step 5: push r_val of store instr as lval's lastest definition
      auto l_val = static_cast<StoreInst *>(instr)->getLval();
      auto r_val = static_cast<StoreInst *>(instr)->getRval();
      if (!IS_GLOBAL_VARIABLE(l_val) && !IS_GEP_INSTR(l_val)) {
        var_val_stack[l_val].emplace_back(r_val);
        wait_delete.emplace_back(instr);
      }
    }
  }
  std::cout << bb->getLLVM_Name() << std::endl;
  for (auto succ_bb : bb->getSuccessor()) {
    std::cout << "\t" + succ_bb->getLLVM_Name() << std::endl;
    for (auto instr : succ_bb->instructionList_) {
      if (instr->isPhi()) {
        auto l_val = static_cast<PhiInst *>(instr)->getLval();
        if (var_val_stack.find(l_val) != var_val_stack.end()) {
          // assert(var_val_stack[l_val].size() != 0);
          // step 6: fill phi pair parameters
          if (var_val_stack[l_val].empty()) {

          } else {
            static_cast<PhiInst *>(instr)->add_phi_pair_operand(
                var_val_stack[l_val].back(), bb);
          }
        }
        // else phi parameter is [ undef, bb ]
      }
    }
  }

  for (auto dom_succ_bb : dominators_->get_dom_tree_succ_blocks(bb)) {
    re_name(dom_succ_bb);
  }

  for (auto instr : bb->instructionList_) {
    // step 7: pop lval's lastest definition
    if (instr->isStore()) {
      auto l_val = static_cast<StoreInst *>(instr)->getLval();
      if (!IS_GLOBAL_VARIABLE(l_val) && !IS_GEP_INSTR(l_val)) {
        var_val_stack[l_val].pop_back();
      }
    } else if (instr->isPhi()) {
      auto l_val = static_cast<PhiInst *>(instr)->getLval();
      if (var_val_stack.find(l_val) != var_val_stack.end()) {
        var_val_stack[l_val].pop_back();
      }
    }
  }

  for (auto instr : wait_delete) {
    bb->deleteInst(instr);
  }
}

void Mem2Reg::remove_alloca() {
  for (auto bb : func_->getBasicBlocks()) {
    std::vector<Instruction *> wait_delete;
    for (auto instr : bb->instructionList_) {
      auto is_alloca = dynamic_cast<AllocaInst *>(instr);
      if (is_alloca) {
        bool is_int =
            is_alloca->getType()->getPtrElementType()->isIntegerType();
        bool is_float =
            is_alloca->getType()->getPtrElementType()->isFloatType();
        if (is_int || is_float) {
          wait_delete.emplace_back(instr);
        }
      }
    }
    for (auto instr : wait_delete) {
      bb->deleteInst(instr);
    }
  }
}