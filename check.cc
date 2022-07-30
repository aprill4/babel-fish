#include "ast.h"
#include "IRBuilder.h"
#include <iostream>
using namespace std;
extern int yyparse();
extern Root *root;
int main(void) {
  yyparse();
  // root->print();
  IRBuilder * irBuilder = new IRBuilder();
  root->generate(irBuilder);
  cout << R"(target triple = "x86_64-pc-linux-gnu")" << endl << endl;
  cout << irBuilder->getModule()->print() << endl;
  return 0;
}