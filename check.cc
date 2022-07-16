#include "ast.h"
#include "IRBuilder.h"
#include <iostream>
using namespace std;
extern int yyparse();
extern Root *root;
int main(void) {
  yyparse();
  root->print();
  // Context &c = *new Context();
  // Module *m = new Module(c, "main_module");
  return 0;
}