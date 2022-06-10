#include <iostream>
#include "ast.h"
using namespace std;
extern int yyparse();
extern Root *root;
int main(void)
{
    yyparse();
    root->print();
    return 0;
}