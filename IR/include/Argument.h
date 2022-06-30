#pragma once
#include "Value.h"

class Function;

class Argument : public Value {
public:
  Argument(Context &c, Type *type, const std::string &name = "", Function *f = nullptr,
           std::size_t argumentNo = 0);
  Function *getFucntion() { return parent_; }
  std::size_t getArgumentNo() const { return argumentNo_; }
  std::string print() override;

private:
  Function *parent_;
  std::size_t argumentNo_;
};