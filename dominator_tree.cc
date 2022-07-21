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
            continue;
        }
        for (auto dom: func->getBasicBlocks()) {
            bb->addDominator(dom);
        }
    }

    isEntry = 1;
    bool changed = 1;
    while (changed) {
        changed = 0;
        for (auto bb: func->getBasicBlocks()) {
            if (isEntry) {
                isEntry = 0;
                continue;
            }
            
            auto dom = bb->getDominators();
            auto new_dom = dom;

            for (auto pre: bb->getPredecessors())
            {
                set<BasicBlock *> intersection;
                auto pre_dom = pre->getDominators();
                set_intersection(new_dom.begin(), new_dom.end(), pre_dom.begin(), pre_dom.end(), inserter(intersection, intersection.begin()));
                new_dom = intersection;
            }

            new_dom.insert(bb);

            if (new_dom != dom) {
                bb->setDominators(new_dom);
                changed = 1;
            }
        }
    }
    return 0;
}