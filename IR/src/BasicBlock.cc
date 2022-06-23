#include "../include/BasicBlock.h"
#include "../include/Function.h"

Module * BasicBlock::getModule(){
    return parent_->getParent();
}
