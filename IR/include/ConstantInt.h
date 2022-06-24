#pragma once

#include "Constant.h"
#include <iostream>

class ConstantInt : public Constant {
public:
  ConstantInt(Type *ty, int val) : Constant(ty, "", 0), value_(val) {
    // std::cout << "1\n";
  }
  std::string print() override;

private:
  ssize_t value_;
};
