#pragma once

#include "Constant.h"
#include "Types/ArrayType.h"

class ConstantArray : public Constant {
public:
  ConstantArray(ArrayType *type, const std::vector<Constant *> &value);
  Constant *getElementValue(int idx);
  std::size_t getArraySize() { return value_.size(); }
  std::string print() override;

public:
  static ConstantArray *get(ArrayType *type,
                            const std::vector<Constant *> &value);

private:
  std::vector<Constant *> value_;
};