#include "BasicBlock.h"
#include "Function.h"
#include "Instruction.h"
#include "Module.h"
#include <cassert>

BasicBlock::BasicBlock(Context &context, const std::string &name,
                       Function *parent)
    : Value(Type::getLabelType(context), name), parent_(parent) {
  assert(parent_ != nullptr);
  parent_->addBasicBlock(this);
}

BasicBlock *BasicBlock::Create(Context &context, const std::string &name,
                               Function *parent) {
  assert(parent != nullptr);
  return new BasicBlock(context, name, parent);
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
}

std::string BasicBlock::print() {
  std::string bb_ir;
  bb_ir += getName();
  bb_ir += ":";
  bb_ir += "\n";
  for (auto instr : instructionList_) {
    bb_ir += "  ";
    bb_ir += instr->print();
    bb_ir += "\n";
  }
  return bb_ir;
}
