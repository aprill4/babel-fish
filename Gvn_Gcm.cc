#include "Gvn_Gcm.h"
#include <sstream>

bool GVN_GCM::isGVN(Value *val) {
  bool is = false;
  if (auto inst = dynamic_cast<Instruction *>(val)) {
    if (inst->isBinary() || inst->isUnary() || inst->isLoad()) {
      is = true;
    }
  } else if (dynamic_cast<GlobalVariable *>(val)) {
    is = true;
  } else if (dynamic_cast<Constant *>(val)) {
    is = true;
  }
  return is;
}

std::string GVN_GCM::get_vn(Value *val) {
  std::stringstream ss;
  if (auto inst = dynamic_cast<Instruction *>(val)) {
    if (inst->isBinary()) {
      ss << "B "
         << "v" << inst->getOperand(0)->getLLVM_Name() << "v"
         << inst->getInstrcutionType() << "v"
         << inst->getOperand(1)->getLLVM_Name();
    } else if (inst->isUnary()) {
      ss << "U" << inst->getInstrcutionType() << "v"
         << inst->getOperand(0)->getLLVM_Name();
    } else if (inst->isLoad()) {
      ss << "L "
         << "v" << inst->getOperand(0)->getLLVM_Name();
    }
  } else if (auto global = dynamic_cast<GlobalVariable *>(val)) {
    ss << "G" << global->getLLVM_Name();
  } else if (dynamic_cast<Constant *>(val)) {
    ss << "C";
    if (auto constant = dynamic_cast<ConstantInt *>(val)) {
      ss << constant->getValue();
    } else if (auto constant = dynamic_cast<ConstantFloat *>(val)) {
      ss << constant->getValue();
    } else if (auto constant = dynamic_cast<ConstantZero *>(val)) {
      ss << "0";
    }
  }
  return ss.str();
}

void GVN_GCM::number_value(Function *func, Value *val) {
  if (auto inst = dynamic_cast<Instruction *>(val)) {
    for (auto op : inst->operands_) {
      number_value(func, op);
    }
  }
  replace_if_already_computed(func, val);
}

void GVN_GCM::replace_if_already_computed(Function *func, Value *val) {
  if (isGVN(val)) {
    std::string vn = get_vn(val);
    auto it = vn_map_.find(vn);
    if (it != vn_map_.end()) {
      val->replaceAllUseWith(it->second);
      if (val != it->second) {
        val->useList_.clear();
      }
    } else {
      vn_map_[vn] = val;
    }
  }
}

void GVN_GCM::run() {
  for (auto f : m_->functionList_) {
    if (f->basicBlocks_.empty()) {
      continue;
    }

    for (auto bb : f->basicBlocks_) {
      vn_map_.clear();
      for (auto inst : bb->instructionList_) {
        number_value(f, inst);
      }
      while (true) {
        std::vector<Instruction *> wait_delete;
        for (auto inst : bb->instructionList_) {
          if (inst->useList_.size() == 0) {
            if (!inst->isTerminator() && !inst->isStore() && !inst->isCall()) {
              wait_delete.emplace_back(inst);
            }
          }
        }
        if (wait_delete.empty()) {
          break;
        }
        for (auto instr : wait_delete) {
          bb->deleteInst(instr);
        }
      }
    }
  }
}
