#include "BasicBlock.h"
#include "Function.h"
#include "Instruction.h"
#include "Module.h"
#include <cassert>

BasicBlock::BasicBlock(Context &context, const std::string &name,
                       Function *parent)
    : Value(context, Type::getLabelType(context), name), parent_(parent) {
  assert(parent_ != nullptr);
  parent_->addBasicBlock(this);
}

BasicBlock *BasicBlock::Create(Context &context, const std::string &name,
                               Function *parent) {
  assert(parent != nullptr);
  return new BasicBlock(context, name, parent);
}

bool BasicBlock::hasTerminator(){
  if (instructionList_.empty()|| !instructionList_.back()->isTerminator()) {
    return false;
  }
  return true;
}

void BasicBlock::eraseFromParent(){
  parent_->remove(this);
}


Module *BasicBlock::getModule() { return parent_->getModule(); }

void BasicBlock::addInstruction(Instruction *instruction) {
  instructionList_.emplace_back(instruction);
}

void BasicBlock::addPredecessor(BasicBlock* pre) {
 predecessorBlocks_.emplace_back(pre);
}

void BasicBlock::addSuccessor(BasicBlock* suc) {
 successorBlocks_.emplace_back(suc);
 suc->addPredecessor(this);
}

void BasicBlock::addDominator(BasicBlock *dom) {
  dominators_.emplace(dom);
}

void BasicBlock::setDominators(std::set<BasicBlock *> &doms) {
  dominators_ = doms;
}


std::set<BasicBlock *>& BasicBlock::getDominators() {
  return dominators_;
}

std::list<BasicBlock *>& BasicBlock::getPredecessors() {
  return predecessorBlocks_;
}

std::string BasicBlock::print() {
  std::string bb_ir;
  bb_ir += getLLVM_Name();
  bb_ir += ":";
  bb_ir += "\n";
  for (auto instr : instructionList_) {
    bb_ir += "  ";
    bb_ir += instr->print();
    bb_ir += "\n";
  }
  return bb_ir;
}
