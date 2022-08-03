#pragma once
#include "IR/include/IR.h"

#include <list>
#include <vector>
#include <cstdio>
#include <string>

struct MachineBasicBlock;
struct MachineModule;
struct MachineFunction;
struct MachineInst;
struct MachineOperand;
struct MReg;
struct Return;

struct MachineModule {
    std::vector<MachineFunction *> functions;
    void print(FILE *fp);
};

struct MachineFunction {
    std::string name;
    std::vector<MachineBasicBlock *> basic_blocks;
    bool call_func = false;
    std::vector<Return*> returns;
    void print(FILE *fp);
};

struct MachineBasicBlock {
    std::string block_name;
    std::vector<MachineBasicBlock *> pres, sucs;
    std::list<MachineInst *> insts;
    MachineFunction* parent = nullptr;
    void print(FILE *fp);
};

struct MachineInst {
    enum Cond { NoCond, Le, Lt, Ge, Gt, Eq, Ne };
    Cond cond = NoCond;

    virtual void print(FILE *fp) {};
    void newline(FILE *fp);
    const char *get_cond();
};

struct Binary : MachineInst {
    enum Op { IAdd, ISub, IMul, IDiv, Mod, FAdd, FSub, FMul, FDiv, ILsl, ILsr, IAsl, IAsr };
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
    Tag tag;
    Cmp() = default;
    Cmp(Tag t, MachineOperand *l , MachineOperand *r): tag(t), lhs(l), rhs(r) {}
    //if tag is Float, `add vmrs APSR_nzcv, FPSCR`
    void print(FILE *fp);
};

struct Mov : MachineInst {
    MachineOperand *dst, *src;
    enum Tag { I2I, F2F, F2I, I2F };
    Tag tag;
    Mov() {}
    Mov(Tag t): tag(t) {}
    Mov(Tag t, MachineOperand *d, MachineOperand *s): tag(t), dst(d), src(s) {}
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
    int arg_count = 0;
    void print(FILE *fp);
};

struct Return : MachineInst {
    bool jump = false;
    std::string jump_name;
    void print(FILE *fp);
};

struct Push_Pop : MachineInst {
    std::vector<MReg *> regs;
    enum Tag { Push, Pop };
    Tag tag;
    void print(FILE *fp);
};

struct MachineOperand {
    enum FlexibleShift { NoShift, Lsl, Lsr, Asl, Asr };
    FlexibleShift shift_type = NoShift;
    int shift_length;

    const char* get_shift();

    virtual const char *print(){ return nullptr; }
};

struct IImm : MachineOperand { 
    int value; 
    IImm(int v): value(v) {}
    const char *print();
};

struct FImm : MachineOperand { 
    float value; 
    FImm(float v): value(v) {}
    const char *print();
};

struct VReg : MachineOperand { 
    int id;
    VReg(int i): id(i) {}
    const char *print();
};

struct MReg : MachineOperand {
    enum Reg { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15,
               s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, 
               fp = r11, ip = r12, sp = r13, lr = r14, pc = r15, };
    Reg reg;
    MReg(Reg r): reg(r) {}

    const char *print();
};

struct Symbol : MachineOperand {
    std::string name;
    const char *print();
};

MachineModule *emit_asm(Module *IR);