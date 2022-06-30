#pragma once

#include "User.h"

class Constant;
class Module;

class GlobalVariable : public User {
public:
  GlobalVariable(Context &c, Type *type, const std::string &globalVarName, bool isConst,
                 Constant *initializer, Module *insertedModule);
  std::string print() override;
  bool isConst() { return isConst_; }
  Constant *getInitValue() { return initValue_; }

public:
  static GlobalVariable *Create(Context &c, Type *type, const std::string &globalVarName,
                                bool isConst, Constant *initializer,
                                Module *insertedModule);

private:
  Constant *initValue_;
  bool isConst_;
};