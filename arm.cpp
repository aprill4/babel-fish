#include "arm.h"
#include "Exception.h"
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
    fprintf(fp, "\n");
}

void MachineBasicBlock::print(FILE *fp) {
    fprintf(fp, "%s:\n", block_name.c_str());
    for (auto inst: insts) {
        fprintf(fp, "  ");
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
    if (operand_type == MachineOperand::Float) {
        sprintf(str, "vf%d", id);
    } else {
        sprintf(str, "vg%d", id);
    }
    return str;
}

const char *MReg::print() {
    const char *mreg_str[] = {
        "", "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15",
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
        "add", "sub", "mul", "div", "", "vadd.f32", "vsub.f32", "vmul.f32", "vdiv.f32", "lsl", "lsr", "asl", "asr"
    };
    fprintf(fp, "%s%s\t%s, %s, %s", op_str[kind], get_cond(), dst->print(), lhs->print(), rhs->print());
}

void Cmp::print(FILE *fp) {
    const char *cmp_inst[] = { "cmp", "vcmp.f32"};
    fprintf(fp, "%s%s\t%s, %s", cmp_inst[tag], get_cond(), lhs->print(), rhs->print());
    if (tag == Float) {
        fprintf(fp, "\nadd\tvmrs APSR_nzcv, FPSCR");
    }
}


void Mov::print(FILE *fp) {
    const char *mv_inst[] = { "mov", "vmov.f32", "vmov", "vmov"};
    if (dynamic_cast<Symbol *>(src)) {
        fprintf(fp, "%s%s\t%s, #:lower:%s", mv_inst[tag], get_cond(), dst->print(), src->print());
        fprintf(fp, "%s%s\t%s, #:upper:%s", mv_inst[tag], get_cond(), dst->print(), src->print());
    } else {
        fprintf(fp, "%s%s\t%s, %s", mv_inst[tag], get_cond(), dst->print(), src->print());
    }
}

void Load::print(FILE *fp) {
    const char *ld_inst[] = { "ldr", "vldr" };
    switch (index_type) {
        case PreIndex:
            fprintf(fp, "%s%s\t%s, [%s, %s%s]!", ld_inst[tag], get_cond(), dst->print(), base->print(), index->print(), index->get_shift());
            break;
        case PostIndex:
            fprintf(fp, "%s%s\t%s, [%s], %s%s", ld_inst[tag], get_cond(), dst->print(), base->print(), index->print(), index->get_shift());
            break;
        case NoIndex: {
            if (offset) {
                fprintf(fp, "%s%s\t%s, [%s, %s]", ld_inst[tag], get_cond(), dst->print(), base->print(), offset->print());
            } else {
                fprintf(fp, "%s%s\t%s, [%s]", ld_inst[tag], get_cond(), dst->print(), base->print());
            }
        } break;
        default: assert(false && "invalid index");
    }
}

void Store::print(FILE *fp) {
    const char *st_inst[] = { "str", "vstr" };
    switch (index_type) {
        case PreIndex:
            fprintf(fp, "%s%s\t%s, [%s, %s%s]!", st_inst[tag], get_cond(), src->print(), base->print(), index->print(), index->get_shift());
            break;
        case PostIndex:
            fprintf(fp, "%s%s\t%s, [%s], %s%s", st_inst[tag], get_cond(), src->print(), base->print(), index->print(), index->get_shift());
            break;
        case NoIndex: {
            if (offset) {
                fprintf(fp, "%s%s\t%s, [%s, %s]", st_inst[tag], get_cond(), src->print(), base->print(), offset->print());
            } else {
                fprintf(fp, "%s%s\t%s, [%s]", st_inst[tag], get_cond(), src->print(), base->print());
            }
        } break;
        default: assert(false && "invalid index");
    }
}

void IClz::print(FILE *fp) {
    fprintf(fp, "clz%s\t%s, %s", get_cond(), dst->print(), src->print());
}

void FNeg::print(FILE *fp) {
    fprintf(fp, "vneg.f32%s\t%s, %s", get_cond(), dst->print(), src->print());
}

void Cvt::print(FILE *fp) {
    const char *cvt_inst[] = { "vcvt.s32.f32", "vcvt.f32.s32" };
    fprintf(fp, "%s%s\t%s, %s", cvt_inst[tag], get_cond(), dst->print(), src->print());
}

void Branch::print(FILE *fp) {
   fprintf(fp, "b%s\t%s", get_cond(), label.c_str());
}

void Call::print(FILE *fp) {
    fprintf(fp, "bl\t%s", callee.c_str());
}

void Return::print(FILE *fp) {
    fprintf(fp, "bx\tlr");
}

void Push_Pop::print(FILE *fp) {
    const char *inst[] = { "push", "pop" };
    fprintf(fp, "%s%s\t{ ", inst[tag], get_cond());
    for (auto reg: regs) {
        fprintf(fp, "%s, ", reg->print());
    }
    fprintf(fp, "}");
}

std::map<Value*, MachineOperand*> v_m;
int vreg_id = 0;
size_t stack_offset = 0;
std::map<Value*, size_t> val_offset;

size_t allocate(size_t size) {
    size_t before_alloca = stack_offset;
    stack_offset += size;
    return before_alloca;
}

MachineOperand::OperandType infer_type_from_value(Value *v) {
    switch (v->type_->typeId_) {
        case Type::IntegerTypeId: return MachineOperand::Int;
        case Type::FloatTypeId: return MachineOperand::Float;
        default: assert(false && "don't support this type");
    }
    return MachineOperand::Undef;
}

// make a virtual register
// if value is given, associate the virtual register with that value.
// (bacause some virtual registers is used to store intermediate result, 
//  so they don't correspond to IR values)
MachineOperand *make_vreg(MachineOperand::OperandType operand_type, Value *v = nullptr) {
    auto vreg = new VReg(vreg_id++, operand_type);
    if (v) {
        v_m[v] = vreg;
    }
    return vreg;
}

MachineOperand *make_operand(Value *v) {
    MachineOperand *ret = nullptr;
    if (v_m.find(v) != v_m.end()) { ret = v_m[v]; }
    else if (auto const_int = dynamic_cast<ConstantInt *>(v)) {
        auto iimm = new IImm(const_int->value_); 
        v_m[v] = iimm;
        ret = iimm;
    } else if (auto const_float = dynamic_cast<ConstantFloat *>(v)) {
        auto fimm = new FImm(const_float->value_);
        v_m[v] = fimm;
        ret = fimm;
    } else {
        assert(false && "don't know what operand you want");
    }

    return ret;

}

void handle_alloca(AllocaInst *inst, MachineBasicBlock *mbb) {
    switch(inst->allocaType_->typeId_) {
        case Type::IntegerTypeId: 
        case Type::FloatTypeId: {
            auto dst = new MReg(MReg::sp);
            //auto lhs = new MReg(MReg::sp);
            auto rhs = new IImm(4);
            auto alloca = new Binary(Binary::Int, Binary::ISub, dst, dst, rhs);
            val_offset[inst] = allocate(4);
            mbb->insts.emplace_back(alloca);
        } break;
        default: assert(false && "don't support this alloca type");
    }
}

void emit_load(Instruction *inst, MachineBasicBlock *mbb) {
    if (auto global = dynamic_cast<GlobalVariable *>(inst->operands_[0])) {
        assert(false && "don't support loading global so far");
    } else {
        auto base = new MReg(MReg::sp);
        auto offset = new IImm(val_offset[inst->operands_[0]]);
        auto ld_tag = Load::Int;
        switch (inst->type_->typeId_) {
            case Type::IntegerTypeId: {
                ld_tag = Load::Int;
            } break;
            case Type::FloatTypeId: {
                ld_tag = Load::Float;
            } break;
            default: assert(false && "don't support this type");
        }
        auto dst = make_vreg(infer_type_from_value(inst), inst);
        auto ld = new Load(dst, base, offset);
        ld->tag = ld_tag;
        mbb->insts.emplace_back(ld);
    }
}

void emit_store(Instruction *inst, MachineBasicBlock *mbb) {
    if (auto global = dynamic_cast<GlobalVariable *>(inst->operands_[0])) {
        assert(false && "don't support loading global so far");
    } else {
        auto base = new MReg(MReg::sp);
        auto offset = new IImm(val_offset[inst->operands_[1]]);
        auto src = make_operand(inst->operands_[0]);
        auto st_tag = Store::Int;
        switch (inst->operands_[0]->type_->typeId_) {
            case Type::IntegerTypeId: {
                st_tag = Store::Int;
            } break;
            case Type::FloatTypeId: {
                st_tag = Store::Float;
            } break;
            default: assert(false && "don't support this type");
        }
        auto st = new Store(src, base, offset);
        st->tag = st_tag;
        mbb->insts.emplace_back(st);
    }
}

void emit_binary(BinaryInst *inst, MachineBasicBlock *mbb) {

    auto lhs = make_operand(inst->operands_[0]);
    auto rhs = make_operand(inst->operands_[1]);
    auto dst = make_vreg(infer_type_from_value(inst), inst);
    Binary *binary_inst;

    if (dynamic_cast<Constant *>(inst->operands_[0])) {
        binary_inst = new Binary(dst, rhs, lhs);
    } else {
        binary_inst = new Binary(dst, lhs, rhs);
    }

    switch(inst->instId_) {
        case Instruction::Add: {
            binary_inst->tag = Binary::Int;
            binary_inst->kind = Binary::IAdd;
            mbb->insts.emplace_back(binary_inst);
        } break;

        case Instruction::Sub: {
            binary_inst->tag = Binary::Int;
            binary_inst->kind = Binary::ISub;
            mbb->insts.emplace_back(binary_inst);
        } break;

        case Instruction::Mul: {
            binary_inst->tag = Binary::Int;
            binary_inst->kind = Binary::IMul;
            mbb->insts.emplace_back(binary_inst);
        } break;

        case Instruction::Sdiv: {
            binary_inst->tag = Binary::Int;
            binary_inst->kind = Binary::IDiv;
            mbb->insts.emplace_back(binary_inst);

        } break;
        
        case Instruction::Mod: {
            assert(false && "not implemented yet.");
        } break;

        case Instruction::Fadd: {
            binary_inst->tag = Binary::Float;
            binary_inst->kind = Binary::FAdd;
            mbb->insts.emplace_back(binary_inst);
        } break;

        case Instruction::Fsub: {
            binary_inst->tag = Binary::Float;
            binary_inst->kind = Binary::FSub;
            mbb->insts.emplace_back(binary_inst);
        }

        case Instruction::Fmul: {
            binary_inst->tag = Binary::Float;
            binary_inst->kind = Binary::FMul;
            mbb->insts.emplace_back(binary_inst);
        } break;

        case Instruction::Fdiv: {
            binary_inst->tag = Binary::Float;
            binary_inst->kind = Binary::FDiv;
            mbb->insts.emplace_back(binary_inst);
        } break;

        default: assert(false && "illegal binary instruction");
    }
}

void emit_ret(ReturnInst *inst, MachineBasicBlock *mbb) {
    auto ret = new Return;
    mbb->insts.emplace_back(ret);
    if (inst->isRetVoid()) {
        return;
    }

    auto mv = new Mov(new MReg(MReg::r0),
                      make_operand(inst->operands_[0]));
    v_m[inst] = mv->dst;
    auto it = mbb->insts.end();
    it--;
    mbb->insts.insert(it, mv);
}

void emit_arg(size_t arg_index, Argument *arg, MachineBasicBlock *entry) {
    if (arg_index > 3) {
        assert(false && "don't support more than 4 arguments, yet");
    }

    // move 
    auto mv = new Mov;
    mv->tag = Mov::I2I;
    mv->src = new MReg(MReg::r0);
    mv->dst = make_vreg(MachineOperand::Int, arg);

    entry->insts.emplace_back(mv);
}

/*
void emit_mov(Value *src, MachineBasicBlock *mbb, Value *dst = nullptr) {
    auto mv = new Mov;
    if (dst){
        //from src to dst
    }

    switch(src->type_->typeId_) {
        case Type::IntegerTypeId: {
            auto src = make_operand(src);
            auto dst = make_operand(src)

        }
    }
    
}
*/
void emit_br(Instruction *inst, MachineBasicBlock *mbb) {
  if (!inst->isBr()) {
    throw Exception(std::string("Inst isn't BranchInst in ") + __FILE__ + " " + std::to_string(__LINE__));
  }  
  if (inst->getOperandNum() == 1) {
    auto br = new Branch();
    br->label = dynamic_cast<BranchInst *>(inst)->getOperand(0)->getLLVM_Name();
    mbb->insts.emplace_back(br);
  } else if (inst->getOperandNum() == 3) {
    auto br1 = new Branch(), br2 = new Branch();
    auto cond = dynamic_cast<BranchInst *>(inst)->getOperand(0);
    br1->label =
        dynamic_cast<BranchInst *>(inst)->getOperand(1)->getLLVM_Name();
    br2->label =
        dynamic_cast<BranchInst *>(inst)->getOperand(2)->getLLVM_Name();
    if (dynamic_cast<IcmpInst *>(cond)) {
      auto condOp = dynamic_cast<IcmpInst *>(cond)->getIcmpOp();
      switch (condOp) {
      case IcmpInst::IcmpOp::EQ:
        br1->cond = MachineInst::Eq;
        break; 
      case IcmpInst::IcmpOp::NEQ:
        br1->cond = MachineInst::Ne;
        break;
      case IcmpInst::IcmpOp::GT:
        br1->cond = MachineInst::Gt;
        break;
      case IcmpInst::IcmpOp::GTE:
        br1->cond = MachineInst::Ge;
        break;
      case IcmpInst::IcmpOp::LT:
        br1->cond = MachineInst::Lt;
        break;
      case IcmpInst::IcmpOp::LTE:
        br1->cond = MachineInst::Le;
        break;
      }
    } else if (dynamic_cast<FcmpInst *>(cond)) {
      auto condOp = dynamic_cast<FcmpInst *>(cond)->getFcmpOp();
      switch (condOp) {
      case FcmpInst::FcmpOp::EQ:
        br1->cond = MachineInst::Eq;
        break; 
      case FcmpInst::FcmpOp::NEQ:
        br1->cond = MachineInst::Ne;
        break;
      case FcmpInst::FcmpOp::GT:
        br1->cond = MachineInst::Gt;
        break;
      case FcmpInst::FcmpOp::GTE:
        br1->cond = MachineInst::Ge;
        break;
      case FcmpInst::FcmpOp::LT:
        br1->cond = MachineInst::Lt;
        break;
      case FcmpInst::FcmpOp::LTE:
        br1->cond = MachineInst::Le;
        break;
      }
    }
    mbb->insts.emplace_back(br1);
    mbb->insts.emplace_back(br2);
  } else {  
    throw Exception("BranchInst's operandNums isn't 1 or 3 and BranchInst's name: " + 
            dynamic_cast<BranchInst *>(inst)->getLLVM_Name()+ __FILE__ + " " + std::to_string(__LINE__));
  }
}

void emit_cmp(Instruction *inst, MachineBasicBlock* mbb) {
  if (!inst->isIcmp() && !inst->isFcmp()) {
    throw Exception(std::string("Inst isn't IcmpInst or FcmpInst in ") + __FILE__ + " " + std::to_string(__LINE__));
  }
  auto cmp = new Cmp();
  if (inst->isIcmp()) {
    cmp->tag = Cmp::Int;
  } else {
    cmp->tag = Cmp::Float;
  }
  cmp->lhs = make_operand(inst->getOperand(0));
  cmp->rhs = make_operand(inst->getOperand(1));
  mbb->insts.emplace_back(cmp);
}

void emit_cvt(Instruction *inst, MachineBasicBlock *mbb) {
    auto cvt = new Cvt();
    cvt->tag = inst->isFp2si() ? Cvt::F2S : Cvt::S2F;
    cvt->src = make_operand(inst->getOperand(0));

    // conversion must happen in fp registers.
    // so check if `src` is in `r` registers,
    // if so, emit a `fmov vr, src`, and change
    // the src to be `vr`
    if (cvt->src->operand_type == MachineOperand::Int) {
        auto fmov = new Mov;
        fmov->src = cvt->src;
        fmov->dst = cvt->src = make_vreg(MachineOperand::Float);
        fmov->tag = Mov::F_I;
        mbb->insts.emplace_back(fmov);
    }

    cvt->dst = make_vreg(MachineOperand::Float, inst);
    mbb->insts.emplace_back(cvt);
}


void emit_call(Instruction *inst, MachineBasicBlock* mbb) {
    auto func_call = dynamic_cast<CallInst*>(inst);
    Function* func = dynamic_cast<Function*>(func_call->getOperand(0));
    Call* call = new Call();
    call->callee = func->getName();
    call->arg_count = func_call->getOperandNum() - 1;
    // for (int i = 0; i < func_call->getOperandNum() - 1; i++) {
    //     auto args = func_call->getOperand(i);
    //     if (i < 3) {
    //         make_operand(args);
    //     } else {
            
    //     }
    // }
    mbb->insts.emplace_back(call);
}

void push_pop(MachineFunction * func){
    auto push = new Push_Pop(), pop = new Push_Pop();
    push->tag = Push_Pop::Push;
    pop->tag = Push_Pop::Pop;
    std::vector<MReg*> push_pop_regs{new MReg(MReg::r11), new MReg(MReg::lr)};
    for (auto reg : push_pop_regs) {
        push->regs.emplace_back(reg);
        pop->regs.emplace_back(reg);    
    }
    auto start = *func->basic_blocks.begin();   // add push to MachineFunction's first MachineBlock
    start->insts.insert(start->insts.begin(), push);

    for (auto bb: func->exit_blocks) {
        auto it = bb->insts.end();
        it--;
        bb->insts.insert(it, pop);
    }
}

void emit_inst(Instruction *inst, MachineBasicBlock *mbb) {
    if (auto ret_inst = dynamic_cast<ReturnInst *>(inst)) { emit_ret(ret_inst, mbb); return; }
    else if (auto binary_inst = dynamic_cast<BinaryInst *>(inst)) { emit_binary(binary_inst, mbb); return; }
    else if (auto alloca_inst = dynamic_cast<AllocaInst *>(inst)) { handle_alloca(alloca_inst, mbb); return; }
    else if (auto icmp_inst = dynamic_cast<IcmpInst *>(inst)) { emit_cmp(icmp_inst, mbb); return; }
    else if (auto fcmp_inst = dynamic_cast<FcmpInst *>(inst)) { emit_cmp(fcmp_inst, mbb); return; }
    else if (auto br_inst = dynamic_cast<BranchInst *>(inst)) { emit_br(br_inst, mbb); return; }
    else if (inst->isCall()) { mbb->parent->call_func = true; emit_call(inst, mbb); return; }
    else if (inst->isLoad()) { emit_load(inst, mbb); return; }
    else if (inst->isStore()) {emit_store(inst, mbb); return; }
    else if (inst->isFp2si() || inst->isSi2fp()) { emit_cvt(inst, mbb); return; }
    assert(false && "illegal instrustion");
}

void emit_bb(BasicBlock *bb, MachineBasicBlock *mbb) {
    mbb->block_name = bb->getLLVM_Name();
    for (auto inst: bb->instructionList_) {
        emit_inst(inst, mbb);
    }
}

MachineFunction *emit_func(Function *func) {
    auto mfunc = new MachineFunction;
    
    mfunc->name = func->name_;

    auto first_bb = true;
    std::map<BasicBlock *, MachineBasicBlock *> bb_map;
    for (auto bb: func->basicBlocks_) {
        auto mbb = new MachineBasicBlock;
        mbb->parent = mfunc;
        if (first_bb) {
            first_bb = false;

            for (size_t i = 0; i < func->arguments_.size(); i++) {
                auto arg = func->arguments_[i];
                emit_arg(i, arg, mbb);
            }
        }
        emit_bb(bb, mbb);
        mfunc->basic_blocks.emplace_back(mbb);
        bb_map[bb] = mbb;
    }

    for (auto bb: func->basicBlocks_) {
        for (auto suc: bb->successorBlocks_) {
            bb_map[bb]->sucs.emplace_back(bb_map[suc]);
            bb_map[suc]->pres.emplace_back(bb_map[bb]);
        }
    }

    if (!stack_offset) { 
        for (auto bb: mfunc->exit_blocks) {
            auto it = bb->insts.end();
            it--;
            auto dst = new MReg(MReg::sp);
            auto rhs = new IImm(stack_offset);
            auto add = new Binary(Binary::Int, Binary::IAdd, dst, dst, rhs);
            bb->insts.insert(it, add);
        }
    }

    if (mfunc->call_func) {    
        push_pop(mfunc);
    }

    return mfunc;
}

MachineModule *emit_asm(Module *IR) {
    auto mm = new MachineModule;

    for (auto func: IR->functionList_) {
        if (func->is_libFn) { continue; }
        auto mfunc = emit_func(func);
        mm->functions.emplace_back(mfunc);
    }
    return mm;
}
