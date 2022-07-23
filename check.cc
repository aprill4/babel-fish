#include "ast.h"
#include "IRBuilder.h"
#include <iostream>
using namespace std;
extern int yyparse();
extern Root *root;
int main(void) {
  yyparse();
  IRBuilder * irBuilder = new IRBuilder();
  root->generate(irBuilder);
  cout << irBuilder->getModule()->print() << endl;
  return 0;
}