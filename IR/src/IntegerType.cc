#include "../include/IntegerType.h"

IntegerType::IntegerType(std::size_t bitsNum)
    : Type(TypeId::IntegerTypeId), bitsNum_(bitsNum) {}

std::size_t IntegerType::getBitsNum() { return bitsNum_; }

IntegerType *IntegerType::get(std::size_t bitsNum) {
  return new IntegerType(bitsNum);
}
