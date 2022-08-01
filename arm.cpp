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
        "add", "sub", "mul", "div", "vadd.f32", "vsub.f32", "vmul.f32", "vdiv.f32", "lsl", "lsr", "asl", "asr"
    };
    fprintf(fp, "%s%s %s, %s, %s", op_str[kind], get_cond(), dst->print(), lhs->print(), rhs->print());
}

void Cmp::print(FILE *fp) {
    const char *cmp_inst[] = { "cmp", "vcmp.f32"};
    fprintf(fp, "%s%s %s, %s", cmp_inst[tag], get_cond(), lhs->print(), rhs->print());
}


void Mov::print(FILE *fp) {
    const char *mv_inst[] = { "mov", "vmov.f32", "vmov", "vmov"};
    if (dynamic_cast<Symbol *>(src)) {
        fprintf(fp, "%s%s %s, #:lower:%s", mv_inst[tag], get_cond(), dst->print(), src->print());
        fprintf(fp, "%s%s %s, #:upper:%s", mv_inst[tag], get_cond(), dst->print(), src->print());
    } else {
        fprintf(fp, "%s%s %s, %s", mv_inst[tag], get_cond(), dst->print(), src->print());
    }
}

void Ld_St::print(FILE *fp) {
    const char *ld_st_inst[] = { "ldr", "str", "vldr", "vstr" };
    switch (index_type) {
        case PreIndex:
            fprintf(fp, "%s%s %s, [%s, %s%s]!", ld_st_inst[tag], get_cond(), dst->print(), base->print(), index->print(), index->get_shift());
            break;
        case PostIndex:
            fprintf(fp, "%s%s %s, [%s], %s%s", ld_st_inst[tag], get_cond(), dst->print(), base->print(), index->print(), index->get_shift());
            break;
        case NoIndex: {
                if (offset) {
                    fprintf(fp, "%s%s %s, [%s, %s]", ld_st_inst[tag], get_cond(), dst->print(), base->print(), offset->print());
                } else {
                    fprintf(fp, "%s%s %s, [%s]", ld_st_inst[tag], get_cond(), dst->print(), base->print());
                }
            }
            break;
    }
}

void IClz::print(FILE *fp) {
    fprintf(fp, "clz%s %s, %s", get_cond(), dst->print(), src->print());
}

void FNeg::print(FILE *fp) {
    fprintf(fp, "vneg.f32%s %s, %s", get_cond(), dst->print(), src->print());
}

void Cvt::print(FILE *fp) {
    const char *cvt_inst[] = { "vcvt.s32.f32", "vcvt.f32.s32" };
    fprintf(fp, "%s%s %s, %s", cvt_inst[tag], get_cond(), dst->print(), src->print());
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

void Push_Pop::print(FILE *fp) {
    const char *inst[] = { "push", "pop" };
    fprintf(fp, "%s%s { ", inst[tag], get_cond());
    for (auto reg: regs) {
        fprintf(fp, "%s, ", reg->print());
    }
    fprintf(fp, "}");
}

std::map<Value*, MachineOperand*> v_m;
static int vreg_id = 0;

MachineOperand *make_operand(Value *v, bool isVreg = false) {
    if (v_m.find(v) != v_m.end()) { return v_m[v]; }
    else if (auto const_int = dynamic_cast<ConstantInt *>(v)) {
        auto iimm = new IImm(const_int->value_); 
        v_m[v] = iimm;
        return iimm;
    } else if (auto const_float = dynamic_cast<ConstantFloat *>(v)) {
        auto fimm = new FImm(const_float->value_);
        v_m[v] = fimm;
        return fimm;
    } else {
        auto vreg = new VReg(vreg_id++);
        v_m[v] = vreg;
        return vreg;
    }
    assert(false && "invalid value");
    return nullptr;
}

void emit_binary(BinaryInst *inst, MachineBasicBlock *mbb) {
    auto const_l = dynamic_cast<Constant *>(inst->operands_[0]);
    auto const_r = dynamic_cast<Constant *>(inst->operands_[1]);
    bool both_const = const_l && const_r;

    auto binary_inst = new Binary;
    binary_inst->dst = make_operand(inst);
    switch(inst->instId_) {
        case Instruction::Add: {
            auto src = make_operand(inst);

            auto lhs = make_operand(inst->operands_[0]);
            auto rhs = make_operand(inst->operands_[1]);


        } break;

        case Instruction::Sub: {

        } break;

        case Instruction::Mul: {

        } break;

        case Instruction::Sdiv: {

        } break;
        
        case Instruction::Mod: {

        } break;

        case Instruction::Fadd: {

        } break;

        case Instruction::Fsub: {

        }

        case Instruction::Fmul: {

        } break;

        case Instruction::Fdiv: {

        } break;

        case Instruction::And: {

        } break;
         
        case Instruction::Or: {

        } break;

        default: printf("illegal binary instruction\n");
    }
}

void emit_ret(ReturnInst *inst, MachineBasicBlock *mbb) {
    auto ret = new Return;
    mbb->insts.emplace_back(ret);
    if (inst->isRetVoid()) {
        return;
    }

    auto mv = new Mov;
    auto ret_val = inst->operands_[0];
    if (ret_val->type_->typeId_== Type::IntegerTypeId) {
        mv->tag = Mov::I2I;
    } else {
        assert(false && "don't support returning float value so far");
        mv->tag = Mov::F2I;
    }
    mv->dst = new MReg(MReg::r0);
    v_m[inst] = mv->dst;
    mv->src = make_operand(inst->operands_[0]);
    auto it = mbb->insts.end();
    it--;
    mbb->insts.insert(it, mv);
}

void emit_mov(Instruction *inst, MachineBasicBlock *mbb) {

    
}

void emit_inst(Instruction *inst, MachineBasicBlock *mbb) {
    
    if (auto ret_inst = dynamic_cast<ReturnInst *>(inst)) { emit_ret(ret_inst, mbb); return; }
    else if (auto binary_inst = dynamic_cast<BinaryInst *>(inst)) { emit_binary(binary_inst, mbb); return; }
    assert(false && "illegal instrustion");
}

MachineBasicBlock *emit_bb(BasicBlock *bb) {
    auto mbb = new MachineBasicBlock;

    for (auto inst: bb->instructionList_) {
        emit_inst(inst, mbb);
        /*
        if (inst->isCall()) {
            //insert `push {lr}` at the head of the instruction list
            continue;
        } else if (inst->isRet()) {
            mbb->insts.emplace_back(new Return);
            continue;
        }
        */
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
