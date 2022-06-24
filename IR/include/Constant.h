#pragma once
#include "User.h"

class Constant : public User {
public:
  Constant(Type *ty, const std::string &name = "", std::size_t num_ops = 0)
      : User(ty, name, num_ops) {}
  ~Constant() = default;
};