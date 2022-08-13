#pragma once

#include "PassManager.h"
#include <unordered_map>
#include <unordered_set>

class LoopInvHoist : public Pass {
public:
  LoopInvHoist(Module *m) : Pass(m) {}

  void run() override;
};
