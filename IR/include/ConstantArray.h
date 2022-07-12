#pragma once

#include "Constant.h"
#include "Types/ArrayType.h"

class ConstantArray : public Constant {
public:
  ConstantArray(Context &c, ArrayType *type, const std::vector<Constant *> &value, const std::vector<int> &dimension);
  Constant *getElementValue(int idx);
  std::string print() override;

public:
  static ConstantArray *get(Context &c, ArrayType *type,
                            const std::vector<Constant *> &value,
                            const std::vector<int> &dimension);

public:
  std::vector<Constant *> value_;
  std::vector<int> dimension_; //e.g. const int a[1][2][3] ,dimensions_ = {1, 2, 3}
};