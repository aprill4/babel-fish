#include "arm.h"
#include "Exception.h"
#include <assert.h>

void print_globals(FILE *fp, const std::set<GlobalVariable *> &globals);

void MachineModule::print(FILE *fp) {
    for (auto func: functions) {
        func->print(fp);
    }

    // print globals
    print_globals(fp, ir_module->globalVariableList_);
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
        "add", "sub", "mul", "div", "", "vadd.f32", "vsub.f32", "vmul.f32", "vdiv.f32", "lsl", "lsr", "asl", "asr","rsb"
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
        fprintf(fp, "%sw%s\t%s, #:lower:%s\n", mv_inst[tag], get_cond(), dst->print(), src->print());
        fprintf(fp, "  %st%s\t%s, #:upper:%s", mv_inst[tag], get_cond(), dst->print(), src->print());
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
    fprintf(fp, "\b\b }");
}

std::map<Value*, MachineOperand*> v_m;
int vreg_id = 0;
size_t stack_offset = 0;
std::map<Value*, size_t> val_offset;

size_t allocate(size_t size) {
    auto before_alloca = stack_offset;
    stack_offset += size;
    return before_alloca;
}

bool can_be_iimm_ror(int x) {
    int v = x;
    for (int r = 0; r < 31; r += 2) {
        if ((v & 0xff) == v) {
            return true;
        }
        v = (v >> 2) | (v << 30);
    }
    return false;
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
    else if (auto const_val = dynamic_cast<Constant *>(v)) {
        int val = 0;
        if (auto const_int = dynamic_cast<ConstantInt *>(const_val)) {
            val = const_int->value_;
        } else if (auto const_float = dynamic_cast<ConstantFloat *>(const_val)) {
            int *p = (int *)&(const_float->value_);
            val = *p;
        }

        if (can_be_iimm_ror(val)) {
            auto imm = new IImm(val);
            v_m[v] = imm;
            ret = imm;
        }
    } else {
        assert(false && "don't know what operand you want");
    }
    return ret;
}

void handle_alloca(AllocaInst *inst, MachineBasicBlock *mbb) {
    auto dst = new MReg(MReg::fp);
    auto src = new MReg(MReg::sp);
    auto mv = new Mov(Mov::I2I, dst, src);
    mbb->insts.emplace_back(mv);

    switch(inst->allocaType_->typeId_) {
        case Type::IntegerTypeId: 
        case Type::FloatTypeId: {
            val_offset[inst] = allocate(4);
        } break;
        case Type::ArrayTypeId: {
            auto array_type = static_cast<ArrayType *>(inst->allocaType_);
            auto array_size = array_type->elementNum_;
            val_offset[inst] = allocate(4 * array_size);
        }
        default: assert(false && "don't support this alloca type");
    }
}

Mov *emit_load_global_addr(GlobalVariable *global) {
    auto addr_reg = make_vreg(MachineOperand::Int);
    auto symbol = new Symbol(global->getName());
    auto load_addr = new Mov(Mov::I2I, addr_reg, symbol);
    return load_addr;
}

void emit_load(Instruction *inst, MachineBasicBlock *mbb) {
    if (auto global = dynamic_cast<GlobalVariable *>(inst->operands_[0])) {
        auto load_addr = emit_load_global_addr(global);
        mbb->insts.emplace_back(load_addr);

        // todo: de-duplicate
        auto base = load_addr->dst;
        auto offset = nullptr;
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
    if (auto global = dynamic_cast<GlobalVariable *>(inst->operands_[1])) {
        auto load_addr = emit_load_global_addr(global);
        mbb->insts.emplace_back(load_addr);

        // todo: de-duplicate
        auto base = load_addr->dst;
        auto offset = nullptr;
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
    mbb->parent->exit_blocks.emplace_back(mbb);
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


void emit_unary(Instruction *inst, MachineBasicBlock* mbb){
    auto unary_inst = dynamic_cast<UnaryInst*>(inst);
    auto right_val = unary_inst->getOperand(0);
    switch (unary_inst->getInstrcutionType()) {
        case Instruction::InstId::Not:
            if (unary_inst->getType()->isIntegerType()) {
                auto clz = new IClz();
                clz->src = make_operand(right_val);
                clz->dst = make_vreg(MachineOperand::OperandType::Int);
                auto lsr = new Binary(Binary::Int, Binary::ILsr, 
                    make_vreg(MachineOperand::OperandType::Int, unary_inst), clz->dst, new IImm(5));
                mbb->insts.emplace_back(clz);
                mbb->insts.emplace_back(lsr);
            } else { 
                // need to add
                auto cmp = new Cmp(Cmp::Float, make_operand(right_val), new FImm(0));
                auto mov1 = new Mov(Mov::I2I, 
                    make_vreg(MachineOperand::OperandType::Int, unary_inst), new IImm(0));
                auto mov2 = new Mov(Mov::I2I, make_operand(unary_inst), new IImm(1));
                mov2->cond = MachineInst::Eq;
                mbb->insts.emplace_back(cmp);
                mbb->insts.emplace_back(mov1);
                mbb->insts.emplace_back(mov2);
            }
        break;
        case Instruction::InstId::Negative:
            if (unary_inst->getType()->isIntegerType()) {
                auto rsb = new Binary(Binary::Int, Binary::Rsb, 
                    make_vreg(MachineOperand::OperandType::Int, unary_inst),
                    make_operand(right_val),
                    new IImm(0));
                mbb->insts.emplace_back(rsb);     
            } else { 
                auto fneg = new FNeg();
                fneg->src = make_operand(right_val);
                fneg->dst = make_vreg(MachineOperand::OperandType::Int, unary_inst);
                mbb->insts.emplace_back(fneg);
            }
        break;
        default:
        break;
    }
}

void emit_gep(Instruction *inst, MachineBasicBlock* mbb) {
    auto gep = dynamic_cast<GetElementPtrInst*>(inst);
    auto res = make_vreg(MachineOperand::OperandType::Int, gep);
    auto ptr = gep->getOperand(0);
    auto element_type = ptr->getType()->getPtrElementType();
    if (element_type->isArrayType()) {
        ArrayType *arr_ty = static_cast<ArrayType *>(element_type);
        for (int i = 0; i < gep->getOperandNum(); i++) {
            auto item = gep->getOperand(i);
            auto m_operand = make_operand(item);
            Binary* offset;
            MachineOperand* offset_operand = make_vreg(MachineOperand::OperandType::Int);
            if (i == 0) {
                offset = new Binary(Binary::Int, Binary::IMul, 
                    offset_operand, m_operand, new IImm(arr_ty->getElementNum()));
            } else {
                element_type = arr_ty->getElementType();
                if (element_type->isArrayType()) {
                    arr_ty = static_cast<ArrayType *>(element_type);
                    offset = new Binary(Binary::Int, Binary::IMul, 
                        offset_operand, m_operand, new IImm(arr_ty->getElementNum()));
                }
            }
            mbb->insts.emplace_back(offset);
            auto offset_sum = new Binary(Binary::Int, Binary::IAdd, res, res, offset_operand);
            mbb->insts.emplace_back(offset_sum);
        }
    } else if (element_type->isPointerType()) {
        ArrayType *arr_ty = static_cast<ArrayType *>(element_type->getPtrElementType());
        for (int i = 0; i < gep->getOperandNum(); i++) {
            auto item = gep->getOperand(i);
            auto m_operand = make_operand(item);
            Binary* offset;
            MachineOperand* offset_operand = make_vreg(MachineOperand::OperandType::Int);
            if (i == 0) {
                offset = new Binary(Binary::Int, Binary::IMul, 
                    offset_operand, m_operand, new IImm(arr_ty->getElementNum()));
            } else {            
                element_type = arr_ty->getElementType();
                if (element_type->isArrayType()) {
                    arr_ty = static_cast<ArrayType *>(element_type);
                    offset = new Binary(Binary::Int, Binary::IMul, 
                        offset_operand, m_operand, new IImm(arr_ty->getElementNum()));
                }
            }
            mbb->insts.emplace_back(offset);
            auto offset_sum = new Binary(Binary::Int, Binary::IAdd, res, res, offset_operand);
            mbb->insts.emplace_back(offset_sum);
        }
    }
}

void emit_call(Instruction *inst, MachineBasicBlock* mbb) {
    auto func_call = dynamic_cast<CallInst*>(inst);
    Function* func = dynamic_cast<Function*>(func_call->getOperand(0));
    Call* call = new Call();
    call->callee = func->getName();
    call->arg_count = func_call->getOperandNum() - 1;

    for (int i = 1; i < func_call->getOperandNum(); i++) {
        auto args = func_call->getOperand(i);
        if (i <= 4) {
            auto mreg = new MReg(MReg::Reg(i));
            auto mv = new Mov();
            // TO_DO: add mv's property;
            mv->src = make_operand(args);
            mv->dst = mreg;
        } else {
            // TO_DO: xxx;
            // auto mv = new Mov();
        }
    }
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
    else if (auto unary_inst = dynamic_cast<UnaryInst *>(inst)) { emit_unary(unary_inst, mbb); return; }
    else if (auto alloca_inst = dynamic_cast<AllocaInst *>(inst)) { handle_alloca(alloca_inst, mbb); return; }
    else if (auto icmp_inst = dynamic_cast<IcmpInst *>(inst)) { emit_cmp(icmp_inst, mbb); return; }
    else if (auto fcmp_inst = dynamic_cast<FcmpInst *>(inst)) { emit_cmp(fcmp_inst, mbb); return; }
    else if (auto br_inst = dynamic_cast<BranchInst *>(inst)) { emit_br(br_inst, mbb); return; }
    else if (inst->isCall()) { mbb->parent->call_func = true; emit_call(inst, mbb); return; }
    else if (inst->isLoad()) { emit_load(inst, mbb); return; }
    else if (inst->isStore()) {emit_store(inst, mbb); return; }
    else if (inst->isFp2si() || inst->isSi2fp()) { emit_cvt(inst, mbb); return; }
    else if (inst->isGep()) {  return; }
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

    if (stack_offset) { 
        // insert `sub sp, sp, stack_offset` to the beginning of the entry block
        auto entry_bb = mfunc->basic_blocks[0];
        auto dst = new MReg(MReg::sp);
        auto offset = new IImm(stack_offset);
        auto sub = new Binary(Binary::Int, Binary::ISub, dst, dst, offset);
        entry_bb->insts.emplace_front(sub);
        // add sp, sp, stack_offset
        for (auto bb: mfunc->exit_blocks) {
            auto it = bb->insts.end();
            it--;
            auto add = new Binary(Binary::Int, Binary::IAdd, dst, dst, offset);
            bb->insts.insert(it, add);
        }
    }

    if (mfunc->call_func) {    
        push_pop(mfunc);
    }

    return mfunc;
}

void print_globals(FILE *fp, const std::set<GlobalVariable *> &globals) {
    fprintf(fp, "\n; here are the globals +-+^_^+-=\n");
    for (auto &glob : globals) {
        fprintf(fp, "%s:\n", glob->getName().c_str());
        auto init = glob->getInitValue();
        if (auto f = dynamic_cast<ConstantFloat *>(init)) {
            float value = f->getValue();
            int same_value_but_in_digits = *((int *) &value);
            fprintf(fp, "  .word\t%d", same_value_but_in_digits);
        } else if (auto i = dynamic_cast<ConstantInt *>(init)) {
            int value = i->getValue();
            fprintf(fp, "  .word\t%d", value);
        } else if (auto arr = dynamic_cast<ConstantArray *>(init)) {
            // TODO: Merge consecutive zeros
            int consecutive_zeros = 0;
            for (auto item : arr->value_) {
                int value;
                bool nonzero = false;
                if (auto f = dynamic_cast<ConstantFloat *>(item)) {
                    float fv = f->getValue();
                    value = *((int *) &fv);
                    nonzero = true;
                } else if (auto i = dynamic_cast<ConstantInt *>(item)) {
                    value = i->getValue();
                    nonzero = true;
                } else if (dynamic_cast<ConstantZero *>(item)) {
                    consecutive_zeros++;
                    continue;
                } else {
                    assert(false && "what is this element");
                }

                if (nonzero && consecutive_zeros != 0) {
                    consecutive_zeros = 0;
                    fprintf(fp, "  .zero\t%d\n", consecutive_zeros * 4);
                }

                fprintf(fp, "  .word\t%d\n", value);
            }

            // print remaining zeros
            if (consecutive_zeros != 0) {
                fprintf(fp, "  .zero\t%d\n", consecutive_zeros * 4);
            }

        } else {
            assert(false && "what is this global");
        }
        fprintf(fp, "\n");
    }
}

MachineModule *emit_asm(Module *IR) {
    auto mm = new MachineModule;
    mm->ir_module = IR;

    // emit functions
    for (auto func: IR->functionList_) {
        if (func->is_libFn) { continue; }
        auto mfunc = emit_func(func);
        mm->functions.emplace_back(mfunc);
    }

    return mm;
}
