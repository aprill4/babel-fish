#pragma once

#include "Constant.h"
#include "Types/ArrayType.h"

class ConstantArray : public Constant {
public:
  ConstantArray(Context &c, ArrayType *type, const std::vector<Value *> &value, const std::vector<int> &dimension);
  Value *getElementValue(int idx);
  std::string print() override;

public:
  static ConstantArray *get(Context &c, ArrayType *type,
                            const std::vector<Value *> &value,
                            const std::vector<int> &dimension);

public:
  std::vector<Value *> value_;
  //to locate the element from indice(format: e.g. const int a[1][2][3] ,dimensions_ = {1, 2, 3})
  std::vector<int> dimension_;
};