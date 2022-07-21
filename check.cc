#include "ast.h"
#include "IRBuilder.h"
#include <iostream>
using namespace std;
extern int yyparse();
extern Root *root;
int main(void) {
  yyparse();
  root->print();
  IRBuilder * irBuilder = new IRBuilder();
  root->generate(irBuilder);
  cout << irBuilder->getModule()->print() << endl;
  // for (auto& glob : irBuilder->getModule()->globalVariableList_) {
  //   cout << glob->print() << endl;
  // }
  // for (auto& glob : irBuilder->getModule()->globalVariableList_) {
  //   cout << glob->print() << endl;
  // }
  // Context &c = *new Context();
  // Module *m = new Module(c, "main_module");
  return 0;
}