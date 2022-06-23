#include "../include/Use.h"

Use::Use(User *user,Value* value) : user_(user),value_(value) {}

Value *Use::getValue() { return value_; }

User *Use::getUser() { return user_; }
