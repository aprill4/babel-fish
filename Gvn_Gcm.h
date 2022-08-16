#pragma once
#include "IR.h"
#include "PassManager.h"

class GVN_GCM : public Pass {
public:
  GVN_GCM(Module *m) : Pass(m) {}
  ~GVN_GCM(){};
  void run() override;

private:
  std::string get_vn(Value *val);
  void number_value(Function *func, Value *val);
  void replace_if_already_computed(Function *func, Value *val);
  bool isGVN(Value *val);
//   std::vector<Instruction*> wait_delete_inst;
  std::unordered_map<std::string, Value *> vn_map_;
  std::unordered_map<Value *, bool> visited_;
};
