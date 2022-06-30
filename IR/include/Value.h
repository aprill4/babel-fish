#pragma once
#include <list>
#include <memory>
#include <string>
#include "Use.h"
#include "Context.h"

class Type;

class Value {
public:
  explicit Value(Type *type, const std::string &name = "");
  explicit Value(Context &c, Type *type, const std::string &name = "");

  virtual ~Value() = default;

  Type *getType();

  bool setName(const std::string &name);
  std::string getName();
  std::string getLLVM_Name();

  void addUse(const Use &u);
  virtual std::string print() = 0;

  size_t getNO();

private:
  Type *type_;
  std::string name_;
  std::list<Use> useList_;
  size_t no_;
};