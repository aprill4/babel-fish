
#pragma once
#include "IR.h"

#include <cstdio>
#include <algorithm>
struct MachineBasicBlock;
struct MachineModule;
struct MachineFunction;
struct MachineInst;
struct Binary;

struct MachineOperand {
    enum FlexibleShift { NoShift, Lsl, Lsr, Asl, Asr };
    FlexibleShift shift_type = NoShift;
    int shift_length;

    enum OperandType { Undef, Float, Int };
    OperandType operand_type = Undef;

    const char* get_shift();

    virtual const char *print(){ return nullptr; }
};

struct IImm : MachineOperand { 
    int value; 
    IImm(int v): value(v) {
        operand_type = MachineOperand::Int;
    }
    const char *print();
};

struct FImm : MachineOperand { 
    float value; 
    FImm(float v): value(v) {
        operand_type = MachineOperand::Float;
    }
    const char *print();
};

struct VReg : MachineOperand { 
    int id;
    VReg(int i, MachineOperand::OperandType ty): id(i) {
        operand_type = ty;
    }
    const char *print();
};

struct MReg : MachineOperand {
    enum Reg { undef, r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15,
               s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16, s17, s18, s19, s20, s21, s22, s23, s24, s25, s26, s27, s28, s29, s30, s31,
               fp = r11, ip = r12, sp = r13, lr = r14, pc = r15, };
    Reg reg;
    MReg(Reg r): reg(r) {
        if (r >= r0 && r <= r15) {
            operand_type = MachineOperand::Int;
        } else if (r >= s0 && r <= s15) {
            operand_type = MachineOperand::Float;
        }
    }

    const char *print();
};

struct Symbol : MachineOperand {
    std::string name;

    Symbol(std::string name): name(name) {}

    const char *print();
};

struct MachineModule {
    std::vector<MachineFunction *> functions;
    Module *ir_module;
    void print(FILE *fp);
};

struct MachineFunction {
    std::string name;
    std::vector<MachineBasicBlock *> basic_blocks;
    bool call_func = false;
    bool has_ret_val = false;
    std::vector<MachineBasicBlock *> exit_blocks;

    Binary *stack_sub = nullptr;
    std::vector<Binary *> stack_adds;

    size_t stack_size;
    int vreg_count;

    void print(FILE *fp);
};

struct MachineBasicBlock {
    std::string block_name;
    std::vector<MachineBasicBlock *> pres, sucs;
    std::list<MachineInst *> insts;
    MachineFunction* parent = nullptr;
    //visited used for directives numbering
    bool visited =false;
    void print(FILE *fp);
};

struct MachineInst {
    enum Cond { NoCond, Le, Lt, Ge, Gt, Eq, Ne };
    Cond cond = NoCond;
    //number用于寄存器分配，方便确认变量活性区间是否重合
    int number;
    virtual void print(FILE *fp) {};
    void newline(FILE *fp);
    const char *get_cond();
};

struct Binary : MachineInst {
    enum Op { IAdd, ISub, IMul, IDiv, Mod, FAdd, FSub, FMul, FDiv, ILsl, ILsr, IAsl, IAsr, Rsb };
    Op kind;
    MachineOperand *dst, *lhs, *rhs;

    enum Tag { Int, Float };
    Tag tag;

    Binary(MachineOperand *d, MachineOperand *l, MachineOperand *r): dst(d), lhs(l), rhs(r) {}
    Binary(Tag t, Op k, MachineOperand *d, MachineOperand *l, MachineOperand *r): tag(t), kind(k), dst(d), lhs(l), rhs(r) {}
    void print(FILE *fp);
};

struct Cmp : MachineInst {
    MachineOperand *lhs, *rhs;
    enum Tag { Int, Float };
    Tag tag = Int;
    Cmp() = default;
    Cmp(Tag t, MachineOperand *l , MachineOperand *r): tag(t), lhs(l), rhs(r) {}
    //if tag is Float, `add vmrs APSR_nzcv, FPSCR`
    void print(FILE *fp);
};

struct Mov : MachineInst {
    MachineOperand *dst, *src;
    // FIXME: Not really "interger to float"
    // It's more like "general purpose register to floating point register"
    enum Tag { I2I, F2F, F_I, H2I, L2I };
    Tag tag;
    Mov() {}
    Mov(Tag t): tag(t) {}
    Mov(Tag t, MachineOperand *d, MachineOperand *s): tag(t), dst(d), src(s) {}

    // Infer tag from operand type
    Mov(MachineOperand *d, MachineOperand *s): dst(d), src(s) {
        if (dst->operand_type == src->operand_type) {
            if (dst->operand_type == MachineOperand::Float) {
                tag = F2F;
            } else {
                tag = I2I;
            }
        } else {
            tag = F_I;
        }
    }
    void print(FILE *fp);
};

struct Load : MachineInst {
    MachineOperand *dst, *base, *offset, *index;
    // PostIndex adds index_length to the base after addressing
    // PreIndex adds index_length to the base before addressing
    enum Index { NoIndex, PostIndex, PreIndex };
    Index index_type = NoIndex;
    int index_length;

    enum Tag { Int, Float };
    Tag tag;
    Load(Tag t, MachineOperand *d, MachineOperand *b, MachineOperand *o): tag(t), dst(d), base(b), offset(o) {}
    Load(MachineOperand *d, MachineOperand *b, MachineOperand *o): dst(d), base(b), offset(o) {}
    Load(MachineOperand *d, MachineOperand *b): dst(d), base(b), offset(nullptr) {}
    void print(FILE *fp);
};

struct Store : MachineInst {
    MachineOperand *src, *base, *offset, *index;
    // PostIndex adds index_length to the base after addressing
    // PreIndex adds index_length to the base before addressing
    enum Index { NoIndex, PostIndex, PreIndex };
    Index index_type = NoIndex;
    int index_length;

    enum Tag { Int, Float };
    Tag tag;
    Store(Tag t, MachineOperand *s, MachineOperand *b, MachineOperand *o): tag(t), src(s), base(b), offset(o) {}
    Store(MachineOperand *s, MachineOperand *b, MachineOperand *o): src(s), base(b), offset(o) {}
    Store(MachineOperand *s, MachineOperand *b): src(s), base(b), offset(nullptr) {}
    void print(FILE *fp);
};

struct IClz : MachineInst {
    MachineOperand *dst, *src;
    void print(FILE *fp);
};

struct FNeg : MachineInst {
    MachineOperand *dst, *src;
    void print(FILE *fp);
};

struct Cvt : MachineInst {
    MachineOperand *dst, *src;
    enum Tag { S2F, F2S };
    Tag tag;
    void print(FILE *fp);
};

struct Branch : MachineInst {
    std::string label;
    void print(FILE *fp);
};

struct Call : MachineInst {
    std::string callee;
    enum ArgType  { Int, Float };
    std::vector<ArgType> args_type;
    int arg_count = 0;
    void print(FILE *fp);
};

struct Return : MachineInst {
    void print(FILE *fp);
};

struct Push_Pop : MachineInst {
    std::vector<MReg *> regs;
    enum Tag { Push, Pop };
    Tag tag;
    void print(FILE *fp);
};

MachineModule *emit_asm(Module *IR);
void stack_ra(MachineModule *mod);