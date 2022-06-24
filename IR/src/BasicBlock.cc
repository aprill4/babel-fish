#include "BasicBlock.h"
#include "Function.h"
#include "Module.h"
#include "Instruction.h"

BasicBlock::BasicBlock(const std::string &name, Function *parent)
    : Value(parent->getModule()->getLabelType(), name), parent_(parent) {}

Module *BasicBlock::getModule() { return parent_->getModule(); }
void BasicBlock::addInstruction(Instruction *instruction) {
  instructionList_.emplace_back(instruction);
}

std::string BasicBlock::print() {
  std::string bb_ir;
  bb_ir += getName();
  bb_ir += ":";
  // print prebb
  // if (!get_pre_basic_blocks().empty()) {
    // bb_ir += "                                                ; preds = ";
  // }
  // for (auto bb : this->get_pre_basic_blocks()) {
    // if (bb != *this->get_pre_basic_blocks().begin())
      // bb_ir += ", ";
    // bb_ir += print_as_op(bb, false);
  // }

  // print prebb
  // if (!this->get_parent()) {
    // bb_ir += "\n";
    // bb_ir += "; Error: Block without parent!";
  // }
  bb_ir += "\n";
  for (auto instr : instructionList_) {
    bb_ir += "  ";
    bb_ir += instr->print();
    bb_ir += "\n";
  }

  return bb_ir;
}
