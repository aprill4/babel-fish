#include "BasicBlock.h"
#include "Function.h"

Module * BasicBlock::getModule(){
    return parent_->getParent();
}
