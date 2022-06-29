#pragma once
#include "IR.h"

class IRBuilder {
public:
  IRBuilder() {
    Context &c = *new Context();
    m = new Module(c, "main_module");
  }

private:
  Context c;
  Module *m;
};