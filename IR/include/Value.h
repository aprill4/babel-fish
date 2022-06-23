#pragma once
#include <list>
#include <memory>
#include <string>

class Type;
class Use;

class Value {
public:
  explicit Value(Type *type, const std::string &name = "");
  ~Value();
  Type *getType();
  bool setName(const std::string &name);
  std::string getName();
  void addUse(const Use &u);

private:
  Type *type_;
  std::string name_;
  std::list<Use> useList_;
};