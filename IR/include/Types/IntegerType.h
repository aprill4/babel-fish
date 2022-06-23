#pragma once

#include "Type.h"

class IntegerType : public Type {
public:
  explicit IntegerType(std::size_t bitsNum);
  std::size_t getBitsNum();
  IntegerType *get(std::size_t bitsNum);

private:
  std::size_t bitsNum_;
};