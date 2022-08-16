#pragma once
#include "Dominators.h"
#include "IR.h"
#include "PassManager.h"

class Mem2Reg : public Pass {

public:
  Mem2Reg(Module *m) : Pass(m) {}
  ~Mem2Reg(){};
  void run() override;
  void generate_phi();
  void re_name(BasicBlock *bb);
  void remove_alloca();
  void dead_code_delete();

private:
  Function *func_;
  Dominators *dominators_;
};
