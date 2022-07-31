#include "ast.h"
#include "IRBuilder.h"
#include "arm.h"
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
  
  auto m = irBuilder->getModule();

  cout << m->print() << endl;

  auto mm = emit_asm(m);

  mm->print(stdout);
  return 0;
}