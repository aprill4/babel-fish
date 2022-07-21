#include "Module.h"
#include "BasicBlock.h"
#include "Context.h"
#include "FunctionType.h"
#include "Function.h"

#include <set>
#include <algorithm>
using namespace std;

int main(){
    Context context;
    Module *m = new Module(context, "m");

    FunctionType *ft = FunctionType::get(Type::getVoidType(context));
    Function *func = Function::Create(context, ft, NULL, "ha", m);

    BasicBlock *a = new BasicBlock(context, "A", func);
    BasicBlock *b = new BasicBlock(context, "B", func);
    BasicBlock *c = new BasicBlock(context, "C", func);
    BasicBlock *d = new BasicBlock(context, "D", func);
    BasicBlock *e = new BasicBlock(context, "E", func);

    a->addSuccessor(b);
    a->addSuccessor(c);
    b->addSuccessor(e);
    c->addSuccessor(d);
    d->addSuccessor(e);

    bool isEntry = true;
    for (auto bb: func->getBasicBlocks()) {
        if (isEntry) {
            bb->addDominator(bb);
            isEntry = false;
        }
        for (auto dom: func->getBasicBlocks()) {
            bb->addDominator(dom);
        }
    }

    bool changed = 1;
    while (changed) {
        for (auto bb: func->getBasicBlocks()) {
           set_intersection() 
        }
    }
    return 0;
}