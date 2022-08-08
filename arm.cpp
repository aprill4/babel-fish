#include "arm.h"
#include "Exception.h"
#include <assert.h>
#include <utility>

void print_globals(FILE *fp, const std::set<GlobalVariable *> &globals);

void MachineModule::print(FILE *fp) {
    fprintf(fp, ".arch armv8-a\n");
    fprintf(fp, ".text\n");
    fprintf(fp, ".align 2\n");
    fprintf(fp, ".syntax unified\n");
    fprintf(fp, ".arm\n");
    fprintf(fp, ".global main\n\n");
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
        "", "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "fp", "ip", "sp", "lr", "pc",
        "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "s12", "s13", "s14", "s15", "s16", "s17", "s18", "s19", "s20", "s21", "s22", "s23", "s24", "s25", "s26", "s27", "s28", "s29", "s30", "s31", "s32"
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
        "add", "sub", "mul", "sdiv", "", "vadd.f32", "vsub.f32", "vmul.f32", "vdiv.f32", "lsl", "lsr", "asl", "asr","rsb"
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
    const char *mv_inst[] = { "mov", "vmov.f32", "vmov", "movt", "movw" };
    if (dynamic_cast<Symbol *>(src)) {
        fprintf(fp, "movw%s\t%s, #:lower:%s\n", get_cond(), dst->print(), src->print());
        fprintf(fp, "  movt%s\t%s, #:upper:%s", get_cond(), dst->print(), src->print());
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
    if (tag == 0) {
	    fprintf(fp, "v%s%s\t{ d8, d9, d10, d11, d12, d13, d14, d15 }\n", inst[tag], get_cond());
	    fprintf(fp, "  %s%s\t{ r4, r5, r6, r7, r8, r9, r10, r11, lr }", inst[tag], get_cond());
    } else {
	    fprintf(fp, "%s%s\t{ r4, r5, r6, r7, r8, r9, r10, r11, lr }\n", inst[tag], get_cond());
	    fprintf(fp, "  v%s%s\t{ d8, d9, d10, d11, d12, d13, d14, d15 }", inst[tag], get_cond());
    }
}

//-----------------------------------------------------------------
std::map<Value*, MachineOperand*> v_m;
int vreg_id = 0;
size_t stack_offset = 0;
std::map<Value*, size_t> val_offset;
//-----------------------------------------------------------------

size_t allocate(size_t size) {
    stack_offset += size;
    return stack_offset;
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

// @WARNING: require a careful review 
std::vector<MachineOperand*> get_defs(MachineInst *inst) {
    std::vector<MachineOperand*> res;
    if(auto i = dynamic_cast<Mov*>(inst)) res.emplace_back(i->dst);
    else if(auto i = dynamic_cast<Binary*>(inst)) res.emplace_back(i->dst);
    else if(auto i = dynamic_cast<Call*>(inst)) {
        res.emplace_back(new MReg(MReg::Reg::lr));
        for(int u = MReg::Reg::r0; u < MReg::Reg::r4; u++)
            res.emplace_back(new MReg(MReg::Reg(u)));
        res.emplace_back(new MReg(MReg::Reg::r12));
        for(int u = MReg::Reg::s0; u < MReg::Reg::s16; u++)
            res.emplace_back(new MReg(MReg::Reg(u)));
    }
    else if(auto i = dynamic_cast<Load*>(inst)) res.emplace_back(i->dst);
    else if(auto i = dynamic_cast<IClz*>(inst)) res.emplace_back(i->dst);
    else if(auto i = dynamic_cast<FNeg*>(inst)) res.emplace_back(i->dst);
    else if(auto i = dynamic_cast<Cvt*>(inst)) res.emplace_back(i->dst);
    
    return res; 
}

void replace_defs(MachineInst *inst, MachineOperand *old_opr, MachineOperand *new_opr){
    std::vector<MachineOperand **> defs;

    if(auto i = dynamic_cast<Mov*>(inst)) defs.push_back(&i->dst);
    else if(auto i = dynamic_cast<Binary*>(inst)) defs.push_back(&i->dst);
    else if(auto i = dynamic_cast<Load*>(inst)) defs.push_back(&i->dst);
    else if(auto i = dynamic_cast<IClz*>(inst)) defs.push_back(&i->dst);
    else if(auto i = dynamic_cast<FNeg*>(inst)) defs.push_back(&i->dst);
    else if(auto i = dynamic_cast<Cvt*>(inst)) defs.push_back(&i->dst);

    //assuming old_opr is VReg kind, plz check
    for (auto def : defs) {
        auto v = dynamic_cast<VReg *>(*def);
        auto old_v = dynamic_cast<VReg *>(old_opr);
        assert(v && "def must be a vreg?");
        assert(old_v && "old_v must be a vreg?");
        if (v->id == old_v->id) {
            *def = new_opr;
        }
    }
}

std::vector<MachineOperand*> get_uses(MachineInst *inst, bool has_ret_val) {
    std::vector<MachineOperand*> res;
    if(auto i = dynamic_cast<Mov*>(inst)) res.emplace_back(i->src);
    else if(auto i = dynamic_cast<Binary*>(inst)) {
        res.emplace_back(i->lhs);
        res.emplace_back(i->rhs);
    }
    else if(auto i = dynamic_cast<Cmp*>(inst)) {
        res.emplace_back(i->lhs);
        res.emplace_back(i->rhs);
    }
    else if(auto i = dynamic_cast<Call*>(inst)) {
        int icnt = 0, fcnt = 0;
        for(auto&type: i->args_type)
            if(type == Call::ArgType::Int) icnt++;
            else fcnt++;
        for(int u = MReg::Reg::r0; u < MReg::Reg::r4 && icnt; u++, icnt--)
            res.emplace_back(new MReg(MReg::Reg(u)));
        for(int u = MReg::Reg::s0; u < MReg::Reg::s16 && fcnt; u++, fcnt--)
            res.emplace_back(new MReg(MReg::Reg(u)));
    }
    else if(auto i = dynamic_cast<Store*>(inst)) {
        res.emplace_back(i->src);
        res.emplace_back(i->base);
        res.emplace_back(i->offset);
    }
    else if(auto i = dynamic_cast<Load*>(inst)) {
        res.emplace_back(i->base);
        res.emplace_back(i->offset);
    }
    else if(auto i = dynamic_cast<IClz*>(inst)) 
        res.emplace_back(i->src);
    else if(auto i = dynamic_cast<FNeg*>(inst)) 
        res.emplace_back(i->src);
    else if(auto i = dynamic_cast<Cvt*>(inst)) 
        res.emplace_back(i->src);
    else if(auto i = dynamic_cast<Return*>(inst)) {
        res.emplace_back(new MReg(MReg::Reg::lr));
        if(has_ret_val) res.emplace_back(new MReg(MReg::Reg::r0));
    }
    return res; 
}

void replace_uses(MachineInst *inst, MachineOperand *old_opr, int new_reg){
    std::vector<MachineOperand**>oprs;

    if(auto i = dynamic_cast<Mov*>(inst)) oprs.emplace_back(&(i->src));
    else if(auto i = dynamic_cast<Binary*>(inst)) {
        oprs.emplace_back(&(i->lhs));
        oprs.emplace_back(&(i->rhs));
    }
    else if(auto i = dynamic_cast<Cmp*>(inst)) {
        oprs.emplace_back(&(i->lhs));
        oprs.emplace_back(&(i->rhs));
    }
    else if(auto i = dynamic_cast<Store*>(inst)) {
        oprs.emplace_back(&(i->src));
        oprs.emplace_back(&(i->base));
        oprs.emplace_back(&(i->offset));
    }
    else if(auto i = dynamic_cast<Load*>(inst)) {
        oprs.emplace_back(&(i->base));
        oprs.emplace_back(&(i->offset));
    }
    else if(auto i = dynamic_cast<IClz*>(inst)) 
        oprs.emplace_back(&(i->src));
    else if(auto i = dynamic_cast<FNeg*>(inst)) 
        oprs.emplace_back(&(i->src));
    else if(auto i = dynamic_cast<Cvt*>(inst)) 
        oprs.emplace_back(&(i->src));

    //assuming old_opr is VReg kind, plz check 
    for(auto opr: oprs) 
        if(dynamic_cast<VReg*>(*opr) 
           && dynamic_cast<VReg*>(*opr)->id == dynamic_cast<VReg*>(old_opr)->id) 
            *opr = new MReg(MReg::Reg(new_reg));
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

MachineOperand *make_operand(Value *v, MachineBasicBlock *mbb, bool no_imm = false) {
    MachineOperand *ret = nullptr;
    if (v_m.find(v) != v_m.end()) { ret = v_m[v]; }
    else if (auto const_val = dynamic_cast<Constant *>(v)) {
        int val = 0;
        int is_float = 0;
        if (auto const_int = dynamic_cast<ConstantInt *>(const_val)) {
            val = const_int->value_;
        } else if (auto const_float = dynamic_cast<ConstantFloat *>(const_val)) {
            int *p = (int *)&(const_float->value_);
            val = *p;
            is_float = 1;
        } else if (auto const_zero = dynamic_cast<ConstantZero *>(const_val)) {
            is_float = const_zero->type_->typeId_ == Type::FloatTypeId;
        }

        if (can_be_iimm_ror(val)) {
            auto imm = new IImm(val);
            v_m[v] = imm;
            ret = imm;
            if (no_imm) {
                auto dst = make_vreg(MachineOperand::Int, v);
                auto mv = new Mov(Mov::I2I, dst, imm);
                mbb->insts.emplace_back(mv);
                v_m[v] = dst;
                ret = dst;
            }
        } else {
            auto l_imm = new IImm(0xffff & val);
            auto h_imm = new IImm((val >> 16) & 0xffff);
            auto dst = make_vreg(MachineOperand::Int, v);

            auto mvw = new Mov(Mov::L2I, dst, l_imm);
            auto mvt = new Mov(Mov::H2I, dst, h_imm);

            mbb->insts.emplace_back(mvw);
            mbb->insts.emplace_back(mvt);

            v_m[v] = dst;
            ret = dst;
        }

        if (is_float) {
            auto src = ret;
            auto dst = make_vreg(MachineOperand::Float, v);
            auto mv = new Mov(Mov::F_I, dst, src);
            mbb->insts.emplace_back(mv);
        }
    } else {
        assert(false && "don't know what operand you want");
    }
    assert(ret && "src of mov is nullptr in function make_operand");
    return ret;
}

void handle_alloca(AllocaInst *inst) {
    switch(inst->allocaType_->typeId_) {
        case Type::IntegerTypeId: 
        case Type::PointerTypeId: 
        case Type::FloatTypeId: {
            val_offset[inst] = allocate(4);
        } break;
        case Type::ArrayTypeId: {
            auto array_type = static_cast<ArrayType *>(inst->allocaType_);
            auto array_size = array_type->elementNum_;
            val_offset[inst] = allocate(4 * array_size);
        } break;
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
    } else if (dynamic_cast<AllocaInst *>(inst->operands_[0])){
        auto base = new MReg(MReg::fp);
        auto offset = new IImm(-(val_offset[inst->operands_[0]]));
        auto ld_tag = Load::Int;
        if (inst->type_->typeId_ == Type::FloatTypeId) {
            ld_tag = Load::Float;
        }
        auto dst = make_vreg(infer_type_from_value(inst), inst);
        auto ld = new Load(dst, base, offset);
        ld->tag = ld_tag;
        mbb->insts.emplace_back(ld);
    } else if (auto gep = dynamic_cast<GetElementPtrInst *>(inst->operands_[0])) {
        auto base = make_operand(gep, mbb);
        auto ld_tag = Load::Int;
        if (inst->type_->typeId_ == Type::FloatTypeId) {
            ld_tag = Load::Float;
        }
        auto dst = make_vreg(infer_type_from_value(inst), inst);
        auto ld = new Load(dst, base);
        ld->tag = ld_tag;
        mbb->insts.emplace_back(ld);
    } else {
        assert(false && "load doesn't support this type");
    }
}

void emit_store(Instruction *inst, MachineBasicBlock *mbb) {
    /*
    if (auto const_val = dynamic_cast<Constant *>(inst->operands_[0])) {
        auto imm = make_operand(const_val, mbb);
        auto dst = make_vreg(infer_type_from_value(const_val), const_val);
        int is_int = 0;
        if (dst->operand_type == MachineOperand::Int) {
            is_int = 1;
        }
        auto mv = new Mov(Mov::Tag(is_int + 1), dst, imm);
        mbb->insts.emplace_back(mv);
    }
    */

    if (auto global = dynamic_cast<GlobalVariable *>(inst->operands_[1])) {
        auto load_addr = emit_load_global_addr(global);
        mbb->insts.emplace_back(load_addr);

        // todo: de-duplicate
        auto base = load_addr->dst;
        auto offset = nullptr;
        auto src = make_operand(inst->operands_[0], mbb);
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

    } else if (auto alloca = dynamic_cast<AllocaInst *>(inst->operands_[1])) {
        auto base = new MReg(MReg::fp);
        auto offset = new IImm(-(val_offset[inst->operands_[1]]));
        auto src = make_operand(inst->operands_[0], mbb, true);
        auto st_tag = Store::Int;
        if (inst->operands_[0]->type_->typeId_ == Type::FloatTypeId) {
            st_tag = Store::Float;
        }
        auto st = new Store(src, base, offset);
        st->tag = st_tag;
        mbb->insts.emplace_back(st);
    } else if (auto gep = dynamic_cast<GetElementPtrInst *>(inst->operands_[1])) {
        auto base = make_operand(gep, mbb);
        auto src = make_operand(inst->operands_[0], mbb, true);
        auto st_tag = Store::Int;
        if (inst->operands_[0]->type_->typeId_ == Type::FloatTypeId) {
            st_tag = Store::Float;
        }
        auto st = new Store(src, base);
        st->tag = st_tag;
        mbb->insts.emplace_back(st);
    } 
}

MachineOperand *emit_constant(int c, MachineBasicBlock *mbb) {
    auto dst = make_vreg(MachineOperand::Int);
    if (!can_be_iimm_ror(c)) {
        auto l_imm = new IImm(0xffff & c);
        auto h_imm = new IImm((c >> 16) & 0xffff);

        auto mvw = new Mov(Mov::L2I, dst, l_imm);
        auto mvt = new Mov(Mov::H2I, dst, h_imm);

        mbb->insts.emplace_back(mvw);
        mbb->insts.emplace_back(mvt);
    } else {
        auto src = new IImm(c);
        auto mov = new Mov(Mov::I2I, dst, src);
        mbb->insts.emplace_back(mov);
    }
    return dst;
}

void emit_binary(BinaryInst *inst, MachineBasicBlock *mbb) {

    Binary::Tag tag;
    Binary::Op kind;
    bool associative = false;
    bool can_rhs_be_imm = false;
    bool can_be_easily_handled = true;

    switch(inst->instId_) {
        case Instruction::Add: {
            tag = Binary::Int;
            kind = Binary::IAdd;
            associative = true;
            can_rhs_be_imm = true;
        } break;

        case Instruction::Sub: {
            tag = Binary::Int;
            kind = Binary::ISub;
            associative = false;
            can_rhs_be_imm = true;
        } break;

        case Instruction::Mul: {
            tag = Binary::Int;
            kind = Binary::IMul;
            associative = true;
            can_rhs_be_imm = false;
        } break;

        case Instruction::Sdiv: {
            tag = Binary::Int;
            kind = Binary::IDiv;

            associative = false;
            can_rhs_be_imm = false;
        } break;
        
        case Instruction::Fadd: {
            tag = Binary::Float;
            kind = Binary::FAdd;
            associative = false;
            can_rhs_be_imm = false; // really?
        } break;

        case Instruction::Fsub: {
            tag = Binary::Float;
            kind = Binary::FSub;
        }

        case Instruction::Fmul: {
            tag = Binary::Float;
            kind = Binary::FMul;
            associative = false;
            can_rhs_be_imm = false;
        } break;

        case Instruction::Fdiv: {
            tag = Binary::Float;
            kind = Binary::FDiv;
            associative = false;
            can_rhs_be_imm = false;
        } break;

        default: can_be_easily_handled = false;
    }

    auto lv = inst->operands_[0];
    auto rv = inst->operands_[1];

    if (dynamic_cast<Constant *>(lv) &&
            !dynamic_cast<Constant *>(rv) &&
            associative) {
        std::swap(lv, rv);
    }

    auto lhs = make_operand(lv, mbb, true);
    auto rhs = make_operand(rv, mbb, !can_rhs_be_imm);

    if (can_be_easily_handled) {
        auto dst = make_vreg(infer_type_from_value(inst), inst);

        auto binary_inst = new Binary(dst, lhs, rhs);
        binary_inst->tag = tag;
        binary_inst->kind = kind;
        mbb->insts.emplace_back(binary_inst);

        return;
    }

    switch(inst->instId_) {
        case Instruction::Mod: {
            auto dr = make_vreg(MachineOperand::Int);
            auto div = new Binary(Binary::Int, Binary::IDiv, dr, lhs, rhs);
            mbb->insts.emplace_back(div);
            auto mr = make_vreg(MachineOperand::Int);
            auto mul = new Binary(Binary::Int, Binary::IMul, mr, div->dst, div->rhs);
            mbb->insts.emplace_back(mul);
            auto dst = make_vreg(MachineOperand::Int, inst);
            auto sub = new Binary(Binary::Int, Binary::ISub, dst, div->lhs, mul->dst);
            mbb->insts.emplace_back(sub);
        } break;

        default: assert(false && "unknown binary inst");
    }
}

void emit_ret(ReturnInst *inst, MachineBasicBlock *mbb) {
    mbb->parent->exit_blocks.emplace_back(mbb);

    auto ret = new Return;
    if (inst->isRetVoid()) {
        mbb->insts.emplace_back(ret);
        return;
    }

    auto ty = inst->operands_[0]->getType();
    bool is_int = (ty->isIntegerType() || ty->isPointerType());

    auto mv = new Mov;
    mv->tag = is_int ? Mov::I2I : Mov::F2F;
    mv->dst = new MReg(is_int ? MReg::r0 : MReg::s0);
    mv->src = make_operand(inst->operands_[0], mbb);

    mbb->insts.emplace_back(mv);
    mbb->insts.emplace_back(ret);
}

void emit_args(std::vector<Argument *> &args, MachineBasicBlock *entry) {

    // ints are passed in r0~r3
    // floats are passed in s0~s15
    // and they are passed independently
    int num_of_ints = 0;
    int num_of_floats = 0;

    for (size_t i = 0; i < args.size(); i++) {
        auto arg = args[i];

        auto ty = arg->getType();
        auto is_int = (ty->isPointerType() || ty->isIntegerType());
        printf("is_int: %d\n", is_int);

        auto mv = new Mov;
        mv->tag = is_int ? Mov::I2I : Mov::F2F;
        mv->src = new MReg(MReg::Reg((is_int ? MReg::r0 : MReg::s0) +
                      (is_int ? num_of_ints : num_of_floats)));
        mv->dst = make_vreg(is_int ?
                      MachineOperand::Int : MachineOperand::Float, arg);

        if (is_int) {
            num_of_ints++;
        } else {
            num_of_floats++;
        }

        entry->insts.emplace_back(mv);
    }

    // if (num_of_ints > 4 || num_of_floats > 16) {
    //     assert(false && "don't support passing arguments in stack, yet");
    // }
}

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
  cmp->lhs = make_operand(inst->getOperand(0), mbb);
  cmp->rhs = make_operand(inst->getOperand(1), mbb);
  mbb->insts.emplace_back(cmp);
}

void emit_cvt(Instruction *inst, MachineBasicBlock *mbb) {
    auto cvt = new Cvt();
    cvt->tag = inst->isFp2si() ? Cvt::F2S : Cvt::S2F;
    cvt->src = make_operand(inst->getOperand(0), mbb, true);

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
                clz->src = make_operand(right_val, mbb);
                clz->dst = make_vreg(MachineOperand::OperandType::Int);
                auto lsr = new Binary(Binary::Int, Binary::ILsr, 
                    make_vreg(MachineOperand::OperandType::Int, unary_inst), clz->dst, new IImm(5));
                mbb->insts.emplace_back(clz);
                mbb->insts.emplace_back(lsr);
            } else { 
                // need to add
                auto cmp = new Cmp(Cmp::Float, make_operand(right_val, mbb), new FImm(0));
                auto mov1 = new Mov(Mov::I2I, 
                    make_vreg(MachineOperand::OperandType::Int, unary_inst), new IImm(0));
                auto mov2 = new Mov(Mov::I2I, make_operand(unary_inst, mbb), new IImm(1));
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
                    make_operand(right_val, mbb),
                    new IImm(0));
                mbb->insts.emplace_back(rsb);     
            } else { 
                auto fneg = new FNeg();
                fneg->src = make_operand(right_val, mbb);
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
    auto res = make_vreg(MachineOperand::OperandType::Int, inst);
    auto ptr = gep->getOperand(0);
    mbb->insts.emplace_back(
            new Binary(
                Binary::Int, Binary::ISub, res, new MReg(MReg::fp), new IImm(val_offset[ptr])));
    auto element_type = ptr->getType()->getPtrElementType();
    ArrayType *arr_ty = nullptr;
    if (element_type->isArrayType()) {
        arr_ty = static_cast<ArrayType *>(element_type);        
    } else if (element_type->isPointerType()) {
        arr_ty = static_cast<ArrayType *>(element_type->getPtrElementType());
    }
    auto first_item = gep->getOperand(1);
    if (dynamic_cast<ConstantInt*>(first_item)) {
        if (dynamic_cast<ConstantInt*>(first_item)->getValue() != 0) {        
            auto offset_sum = new Binary(Binary::Int, Binary::IAdd, res, res, 
                        new IImm(dynamic_cast<ConstantInt*>(first_item)->getValue() * arr_ty->getElementNum() * 4));
            mbb->insts.emplace_back(offset_sum);        
        }
    } else {
        auto m_operand = make_operand(first_item, mbb);
        MachineOperand* offset_operand = make_vreg(MachineOperand::OperandType::Int);
        Binary* offset = new Binary(Binary::Int, Binary::IMul, 
            offset_operand, m_operand, new IImm(arr_ty->getElementNum() * 4));
        mbb->insts.emplace_back(offset);
        auto offset_sum = new Binary(Binary::Int, Binary::IAdd, res, res, offset_operand);
        mbb->insts.emplace_back(offset_sum);                
    }
    for (int i = 2; i < gep->getOperandNum(); i++) {
        auto item = gep->getOperand(i);
        if (dynamic_cast<ConstantInt*>(item)) {
            if (dynamic_cast<ConstantInt*>(item)->getValue() != 0) {
                element_type = arr_ty->getElementType();
                std::int32_t offset_num = 0;                
                if (element_type->isArrayType()) {
                    arr_ty = static_cast<ArrayType *>(element_type);
                    offset_num = dynamic_cast<ConstantInt*>(item)->getValue() * arr_ty->getElementNum() * 4;
                } else {
                    offset_num = dynamic_cast<ConstantInt*>(item)->getValue() * 4;
                }
                auto offset_sum = new Binary(Binary::Int, Binary::IAdd, res, res, new IImm(offset_num));
                mbb->insts.emplace_back(offset_sum);                    
            }
        } else {        
            auto m_operand = make_operand(item, mbb);
            MachineOperand* offset_operand = make_vreg(MachineOperand::OperandType::Int);
            element_type = arr_ty->getElementType();
            if (element_type->isArrayType()) {
                arr_ty = static_cast<ArrayType *>(element_type);
            }
            Binary* offset = new Binary(Binary::Int, Binary::IMul, 
                    offset_operand, m_operand, new IImm(arr_ty->getElementNum() * 4));
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
    call->args_type.resize(call->arg_count);
    int32_t int_args_num = 0, float_args_num = 0;
    for (int i = 1; i < func_call->getOperandNum(); i++) {
        auto args = func_call->getOperand(i);
        if (!args->getType()->isFloatType()) {
            int_args_num++;
            call->args_type[i - 1] = Call::Int;
        } else {
            float_args_num++;
            call->args_type[i - 1] = Call::Float;
        }
    }
    int32_t args_offset = ((int_args_num > 4 ?  int_args_num - 4 : 0) 
                + (float_args_num > 16 ?  float_args_num - 16 : 0)) * 4;

    bool sp_subbed = args_offset > 0;
    if (sp_subbed) {
        auto sp_sub = new Binary(Binary::Int, Binary::ISub, 
                new MReg(MReg::sp), new MReg(MReg::sp), new IImm(args_offset));
        mbb->insts.emplace_back(sp_sub);
    }
    int32_t old_args_offset = args_offset;
    args_offset -= 4;
    for (int i = func_call->getOperandNum() - 1; i >= 1 ; i--) {
        auto args = func_call->getOperand(i);
        if (!args->getType()->isFloatType()) {
            if (int_args_num <= 4) {
                auto mreg = new MReg(MReg::Reg(int_args_num));
                auto mv = new Mov(Mov::I2I, mreg, make_operand(args, mbb));
                mbb->insts.emplace_back(mv);                
            } else {
                auto mreg = new MReg(MReg::r3);
                auto mv = new Mov(Mov::I2I, mreg, make_operand(args, mbb));
                auto store = new Store(Store::Int, mreg, new MReg(MReg::sp), new IImm(args_offset));
                mbb->insts.emplace_back(mv);
                mbb->insts.emplace_back(store);              
                args_offset -= 4; 
            }
            int_args_num--;
        } else {
            if (float_args_num <= 16) {
                auto mreg = new MReg(MReg::Reg(float_args_num + 16));
                auto mv = new Mov(Mov::F2F, mreg, make_operand(args, mbb));
                mbb->insts.emplace_back(mv);                
            } else {
                auto mreg = new MReg(MReg::s15);
                auto mv = new Mov(Mov::F2F, mreg, make_operand(args, mbb));
                auto store = new Store(Store::Float, mreg, new MReg(MReg::sp), new IImm(args_offset));
                mbb->insts.emplace_back(mv);
                mbb->insts.emplace_back(store);              
                args_offset -= 4;  
            }
            float_args_num--;
        }
    }
    mbb->insts.emplace_back(call);
    if (sp_subbed) {
        auto sp_add = new Binary(Binary::Int, Binary::IAdd, new MReg(MReg::sp), new MReg(MReg::sp), new IImm(old_args_offset));
        mbb->insts.emplace_back(sp_add);
    }
    if (func_call->getFunctionType()->getReturnType()->isIntegerType()) {
        auto reg_r0 = new MReg(MReg::r0);
        auto ret = make_vreg(MachineOperand::OperandType::Int, inst);
        mbb->insts.emplace_back(new Mov(Mov::I2I, ret, reg_r0));
    } else if (func_call->getFunctionType()->getReturnType()->isFloatType()) {
        auto reg_s0 = new MReg(MReg::s0);
        auto ret = make_vreg(MachineOperand::OperandType::Float, inst);
        mbb->insts.emplace_back(new Mov(Mov::F2F, ret, reg_s0));        
    }
}

void push_pop(MachineFunction * func){
    auto push = new Push_Pop(), pop = new Push_Pop();
    push->tag = Push_Pop::Push;
    pop->tag = Push_Pop::Pop;

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
    else if (auto alloca_inst = dynamic_cast<AllocaInst *>(inst)) { handle_alloca(alloca_inst); return; }
    else if (auto icmp_inst = dynamic_cast<IcmpInst *>(inst)) { emit_cmp(icmp_inst, mbb); return; }
    else if (auto fcmp_inst = dynamic_cast<FcmpInst *>(inst)) { emit_cmp(fcmp_inst, mbb); return; }
    else if (auto br_inst = dynamic_cast<BranchInst *>(inst)) { emit_br(br_inst, mbb); return; }
    else if (inst->isCall()) { mbb->parent->call_func = true; emit_call(inst, mbb); return; }
    else if (inst->isLoad()) { emit_load(inst, mbb); return; }
    else if (inst->isStore()) {emit_store(inst, mbb); return; }
    else if (inst->isFp2si() || inst->isSi2fp()) { emit_cvt(inst, mbb); return; }
    else if (inst->isGep()) { emit_gep(inst, mbb); return; }
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

            emit_args(func->arguments_, mbb);
        }
        emit_bb(bb, mbb);
        mfunc->basic_blocks.emplace_back(mbb);
        bb_map[bb] = mbb;
    }

    mfunc->stack_size = stack_offset;
    mfunc->vreg_count = vreg_id;

    // CFG is not used?
    for (auto bb: func->basicBlocks_) {
        for (auto suc: bb->successorBlocks_) {
            bb_map[bb]->sucs.emplace_back(bb_map[suc]);
            bb_map[suc]->pres.emplace_back(bb_map[bb]);
        }
    }

    //if (stack_offset) { 
    auto entry_bb = mfunc->basic_blocks[0];
    // insert `sub sp, sp, stack_offset` to the beginning of the entry block
    auto dst = new MReg(MReg::sp);
    auto offset = new IImm(stack_offset);
    auto sub = new Binary(Binary::Int, Binary::ISub, dst, dst, offset);
    mfunc->stack_sub = sub;
    entry_bb->insts.emplace_front(sub);
    // mv sp to fp
    auto fp = new MReg(MReg::fp);
    auto sp = new MReg(MReg::sp);
    auto mv = new Mov(Mov::I2I, fp, sp);
    entry_bb->insts.emplace_front(mv);
    // add sp, sp, stack_offset
    for (auto bb: mfunc->exit_blocks) {
        auto it = bb->insts.end();
        it--;
        auto add = new Binary(Binary::Int, Binary::IAdd, dst, dst, offset);
        mfunc->stack_adds.push_back(add);
        bb->insts.insert(it, add);
    }

    stack_offset = 0;
    vreg_id = 0;
    val_offset.clear();
    v_m.clear();
    //}

    return mfunc;
}

void print_globals(FILE *fp, const std::set<GlobalVariable *> &globals) {
    fprintf(fp, "\n@ here are the globals +-+^_^+-=\n");
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

void stack_ra_on_function(MachineFunction *mf)  {
    int callee_size      = 100, //calcation details: (r11 - r4 + 1 + lr + s31 - s16) * 4 = 100
        local_var_size   = mf->stack_size,
        spilled_size     = mf->vreg_count * 4,
        arg_size         = 0;

    // calculate arg size
    if(mf->call_func){
        short max_icnt = 0, max_fcnt = 0;

        for(auto mb : mf->basic_blocks) {
            for(auto inst: mb->insts) {
                if (dynamic_cast<Call*>(inst)) {
                    auto call = dynamic_cast<Call*>(inst);
                    short icnt = 0, fcnt = 0;
                    for(auto&type: call->args_type)
                        if(type == Call::ArgType::Int) icnt++;
                        else fcnt++; 
                    max_icnt = std::max(max_icnt, icnt);
                    max_fcnt = std::max(max_fcnt, fcnt);
                }
            }
        }

        arg_size = std::max(0, max_icnt - 4) * 4 + std::max(0, max_fcnt - 16) * 4;
    }

    // insert stores after defs, loads before uses
    for(auto mb: mf->basic_blocks) {
        auto it = mb->insts.begin(); // for the convenience of insertion into std::list
        for(auto inst: mb->insts) {
            auto defs = get_defs(inst);
            for (auto def : defs) {
                if (!dynamic_cast<VReg*>(def)) continue;
                
                auto actual_reg = dynamic_cast<VReg*>(def);
                bool isInt = actual_reg->operand_type == MachineOperand::OperandType::Int;
                auto str = new Store(isInt ? Store::Tag::Int : Store::Tag::Float,
                                               new MReg(isInt?MReg::Reg::r4 : MReg::Reg::s16),
                                               new MReg(MReg::Reg::fp),
                                               new IImm(-(local_var_size + actual_reg->id * 4) - 4));

                auto it0 = it;
                it0++; //awkward since the api's limitations
                mb->insts.insert(it0, str);
                replace_defs(inst, def, str->src);
            }

            auto uses = get_uses(inst, mf->has_ret_val);
            int ireg = MReg::Reg::r5;
            int freg = MReg::Reg::s17;

            // @TODO uses might be the same??
            for (auto use : uses) {
                if (!dynamic_cast<VReg*>(use)) continue;

                assert(ireg >= MReg::Reg::r5 && ireg <= MReg::Reg::r7);
                assert(freg >= MReg::Reg::s17 && freg <= MReg::Reg::s19);
                auto actual_reg = dynamic_cast<VReg*>(use);
                bool isInt = actual_reg->operand_type == MachineOperand::OperandType::Int;
                int new_reg;
                if(isInt) new_reg = ireg++;
                else new_reg = freg++;

                auto ldr = new Load(isInt ? Load::Tag::Int : Load::Tag::Float,
                                               new MReg(MReg::Reg(new_reg)),
                                               new MReg(MReg::Reg::fp),
                                               new IImm(-(local_var_size + actual_reg->id * 4) - 4));

                mb->insts.insert(it, ldr);
                replace_uses(inst, use, new_reg);
            }
            it++;
        }
    }

    // insert prologue and epilogue
    // insert add/sub sp & push/pops

    auto total_size = local_var_size + spilled_size;
    mf->stack_sub->rhs = new IImm(total_size);
    for (auto stack_add : mf->stack_adds) {
        stack_add->rhs = new IImm(total_size);
    }

    push_pop(mf);

    // fixup local array base calc
    /*for(auto base : f->local_array_bases) {
        assert(base->tag == MI_BINARY);
        auto sub = (MI_Binary *) base;
        assert(sub->op == BINARY_SUBTRACT);
        assert(sub->lhs == make_reg(sp));
        assert(sub->rhs.tag == IMM && sub->rhs.value > 0);

        int32 offset_relative_to_sp = arg_size + spilled_size + local_array_size - sub->rhs.value;
        // @TODO replace with a mov directly
        // if offset relative to sp is 0

        sub->op = BINARY_ADD;
        sub->lhs = make_reg(sp);
        sub->rhs = make_imm(offset_relative_to_sp);

    }


    // fixup arg loading calc
    for(auto mb : f->mbs) {
        for(auto I=mb->inst; I; I=I->next) {
            if (I->tag != MI_LOAD) continue;
            auto ldr = (MI_Load *) I;
            if (!ldr) continue;
            if (ldr->mem_tag != MEM_LOAD_ARG) continue;

            int32 offset_value = ((ldr->offset.tag == SHAYEBUSHI) ? 0 : ldr->offset.value);
            uint32 ofst_rel_to_sp = arg_size + spilled_size + local_array_size + callee_size + offset_value;
            ldr->base.value = sp;
            ldr->offset = make_imm(ofst_rel_to_sp);

        }
    }*/

    // legalize imm, use r12 as temp
    for(auto mb : mf->basic_blocks) {
        auto it = mb->insts.begin();
        for(auto I: mb->insts) {
            auto uses = get_uses(I, mf->has_ret_val);

            bool need_legalize = false;
            MachineOperand *use_of_imm;

            if (auto load = dynamic_cast<Load*>(I)) {
                if (dynamic_cast<IImm*>(load->base)) 
                    goto done;
            }

            if (dynamic_cast<Load*>(I) || dynamic_cast<Store*>(I)) {
                auto load_or_store = static_cast<Load*>(I);
                if (dynamic_cast<IImm*>(load_or_store->offset)) {
                    use_of_imm = load_or_store->offset;
                    int val = dynamic_cast<IImm*>(load_or_store->offset)->value;
                    need_legalize = val < -4095 || val > 4095;
                    goto done;
                }
            }

            for(auto use : uses) {
                if (dynamic_cast<IImm*>(use)) {
                    use_of_imm = use;
                    need_legalize = !can_be_iimm_ror(dynamic_cast<IImm*>(use)->value);
                    goto done;
                }
            }

            done:;

            if (need_legalize) {
                //printf("%d cannot be imm!\n", use_of_imm.value);

                auto temp = new MReg(MReg::Reg::r12);
                auto val = dynamic_cast<IImm *>(use_of_imm)->value;
                auto l_imm = new IImm(0xffff & val);
                auto h_imm = new IImm((val >> 16) & 0xffff);

                auto mvw = new Mov(Mov::L2I, temp, l_imm);
                auto mvt = new Mov(Mov::H2I, temp, h_imm);

                mb->insts.insert(it, mvw);
                mb->insts.insert(it, mvt);
                replace_uses(I, use_of_imm, MReg::Reg::r12);
            }
            it++;
        }
    }
}

void stack_ra(MachineModule *mod) {
    for (auto func: mod->functions) {
        stack_ra_on_function(func);
    }
}
