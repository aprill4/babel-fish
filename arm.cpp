#include "arm.h"
#include <assert.h>

void MachineModule::print(FILE *fp) {
    for (auto func: functions) {
        func->print(fp);
    }
}

void MachineFunction::print(FILE *fp) {
    fprintf(fp, "%s:\n", name.c_str());
    for (auto bb: basic_blocks) {
        bb->print(fp);
    }
}

void MachineBasicBlock::print(FILE *fp) {
    for (auto inst: insts) {
        inst->print(fp);
        inst->newline(fp);
    }
}

const char* MachineOperand::get_shift() {
    const char *shift_str[] = {
        "", "lsl", "lsr", "asr", "ror"
    };

    char *str = new char[20];
    if (shift_type != NoShift) {
        sprintf(str, ", %s #%d", shift_str[shift_type], shift_length);
        return str;
    }

    return "";
}

const char *IImm::print() {
    char *str = new char[12];
    sprintf(str, "#%d", value);
    return str;
}

const char *FImm::print() {
    char *str = new char[20];
    sprintf(str, "#%e", value);
    return str;
}

const char *VReg::print() {
    char *str = new char[12];
    sprintf(str, "v%d", id);
    return str;
}

const char *MReg::print() {
    const char *mreg_str[] = {
        "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15",
        "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "s12", "s13", "s14", "s15",
    };

    return mreg_str[reg];
}

const char *Symbol::print() {
    return name.c_str();
}

void MachineInst::newline(FILE *fp) {
    fprintf(fp, "\n");
}

const char *MachineInst::get_cond() {
    const char *cond_str[] = {
        "", "le", "lt", "ge", "gt", "eq", "ne"
    };
    return cond_str[cond];
}

void Binary::print(FILE *fp) {
    const char *op_str[] = {
        "add", "sub", "mul", "div", "fadd", "fsub", "fmul", "fdiv", "lsl", "lsr", "asl", "asr"
    };
    fprintf(fp, "%s%s %s, %s, %s", op_str[kind], get_cond(), dst->print(), lhs->print(), rhs->print());
}

void ICmp::print(FILE *fp) {
    fprintf(fp, "cmp%s %s, %s", get_cond(), lhs->print(), rhs->print());
}

void FCmp::print(FILE *fp) {
    fprintf(fp, "fcmp%s %s, %s", get_cond(), lhs->print(), rhs->print());
}

void IMov::print(FILE *fp) {
    if (dynamic_cast<Symbol *>(src)) {
        fprintf(fp, "movw%s %s, #:lower:%s", get_cond(), dst->print(), src->print());
        fprintf(fp, "movt%s %s, #:upper:%s", get_cond(), dst->print(), src->print());
    } else {
        fprintf(fp, "mov%s %s, %s", get_cond(), dst->print(), src->print());
    }
}

void FMov::print(FILE *fp) {
    if (dynamic_cast<Symbol *>(src)) {
        fprintf(fp, "movw%s %s, #:lower:%s", get_cond(), dst->print(), src->print());
        fprintf(fp, "movt%s %s, #:upper:%s", get_cond(), dst->print(), src->print());
    } else {
        fprintf(fp, "vmov.f32%s %s, %s", get_cond(), dst->print(), src->print());
    }
}

void ILoad::print(FILE *fp) {
    switch (index_type) {
        case PreIndex:
            fprintf(fp, "ldr%s %s, [%s, %s%s]!", get_cond(), dst->print(), base->print(), index->print(), index->get_shift());
            break;
        case PostIndex:
            fprintf(fp, "ldr%s %s, [%s], %s%s", get_cond(), dst->print(), base->print(), index->print(), index->get_shift());
            break;
        case NoIndex: {
                if (offset) {
                    fprintf(fp, "ldr%s %s, [%s, %s]", get_cond(), dst->print(), base->print(), offset->print());
                } else {
                    fprintf(fp, "ldr%s %s, [%s]", get_cond(), dst->print(), base->print());
                }
            }
            break;
    }
}

void IStore::print(FILE *fp) {
    switch (index_type) {
        case PreIndex:
            fprintf(fp, "str%s %s, [%s, %s%s]!", get_cond(), src->print(), base->print(), index->print(), index->get_shift());
            break;
        case PostIndex:
            fprintf(fp, "str%s %s, [%s], %s%s", get_cond(), src->print(), base->print(), index->print(), index->get_shift());
            break;
        case NoIndex: {
                if (offset) {
                    fprintf(fp, "str%s %s, [%s, %s]", get_cond(), src->print(), base->print(), offset->print());
                } else {
                    fprintf(fp, "str%s %s, [%s]", get_cond(), src->print(), base->print());
                }
            }
            break;
    }
}

void FLoad::print(FILE *fp) {

}

void FStore::print(FILE *fp) {

}

void IClz::print(FILE *fp) {
    fprintf(fp, "clz%s %s, %s", get_cond(), dst->print(), src->print());
}

void FNeg::print(FILE *fp) {
    fprintf(fp, "vneg.f32%s %s, %s", get_cond(), dst->print(), src->print());
}

void F2ICvt::print(FILE *fp) {
    fprintf(fp, "vcvt.s32.f32%s %s, %s", get_cond(), dst->print(), src->print());
}

void I2FCvt::print(FILE *fp) {
    fprintf(fp, "vcvt.f32.s32%s %s, %s", get_cond(), dst->print(), src->print());
}

void Branch::print(FILE *fp) {
   fprintf(fp, "b%s %s", get_cond(), label.c_str());
}

void Call::print(FILE *fp) {
    fprintf(fp, "bl %s", callee.c_str());
}

void Return::print(FILE *fp) {
    fprintf(fp, "bx lr");
}

void Push::print(FILE *fp) {
   fprintf(fp, "push%s { ", get_cond());
   for (auto reg: regs) {
       fprintf(fp, "%s, ", reg->print());
   }
   fprintf(fp, "}");
}

void Pop::print(FILE *fp) {
   fprintf(fp, "pop%s { ", get_cond());
   for (auto reg: regs) {
       fprintf(fp, "%s, ", reg->print());
   }
   fprintf(fp, "}");
}


IMov *emit_ret(Instruction *inst) {
    auto mi = new IMov;

    mi->dst = new MReg(MReg::r0);

    auto value = inst->operands_[0];
    if (auto const_int = dynamic_cast<ConstantInt *>(value)) {
        mi->src = new IImm(const_int->value_);
    }

    return mi;
}

IMov *emit_imov(Instruction *inst) {
    auto imv = new IMov;

    return imv;
}

MachineInst *emit_inst(Instruction *inst) {
    
    if (inst->isRet()) { return emit_ret(inst); }
    assert(false && "illegal instrustion");
    return nullptr;
}

MachineBasicBlock *emit_bb(BasicBlock *bb) {
    auto mbb = new MachineBasicBlock;

    for (auto inst: bb->instructionList_) {
        if (inst->isCall()) {
            //insert `push {lr}` at the head of the instruction list
            continue;
        }

        mbb->insts.emplace_back(emit_inst(inst));
        if (inst->isRet()) {
            mbb->insts.emplace_back(new Return);
        }
    }
    return mbb;
}

MachineFunction *emit_func(Function *func) {
    auto mfunc = new MachineFunction;
    
    mfunc->name = func->name_;

    std::map<BasicBlock *, MachineBasicBlock *> bb_map;
    for (auto bb: func->basicBlocks_) {
        auto mbb = emit_bb(bb);
        mfunc->basic_blocks.emplace_back(mbb);
        bb_map[bb] = mbb;
    }

    for (auto bb: func->basicBlocks_) {
        for (auto suc: bb->successorBlocks_) {
            bb_map[bb]->sucs.emplace_back(bb_map[suc]);
            bb_map[suc]->pres.emplace_back(bb_map[bb]);
        }
    }

    return mfunc;
}

MachineModule *emit_asm (Module *IR) {
    auto mm = new MachineModule;

    for (auto func: IR->functionList_) {
        if (func->is_libFn) { continue; }
        auto mfunc = emit_func(func);
        mm->functions.emplace_back(mfunc);
    }
    return mm;
}
