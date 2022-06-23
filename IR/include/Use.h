#pragma once

class Value;
class User;

class Use {
public:
  Use(User *user,Value*);
  Value *getValue();
  User *getUser();

private:
  User *user_ = nullptr;
  Value *value_ = nullptr;
};