#pragma once

#include <list>
#include <vector>
#include <cstdio>

struct MachineModule {
    std::vector<MachineFunction *> functions;
    void print(FILE *fp);
};

struct MachineFunction {
    std::vector<MachineBasicBlock *> basic_blocks;
    void print(FILE *fp);
};

struct MachineBasicBlock {
    std::vector<MachineBasicBlock *> pres, sucs;
    std::list<MachineInst *> insts;
    void print(FILE *fp);
};

struct MachineInst {
    enum Cond { NoCond, Le, Lt, Ge, Gt, Eq, Ne };
    Cond cond = NoCond;

    enum FlexibleShift { NoShift, Lsl, Lsr, Asl, Asr };
    FlexibleShift shift_type = NoShift;
    int shift_length;

    virtual void print(FILE *fp);
};

struct Binary : MachineInst {
    enum Op { IAdd, ISub, IMul, IDiv, FAdd, FSub, FMul, FDiv, ILsl, ILsr, IAsl, IAsr };
    Op kind;
    MachineOperand *dst, *lhs, *rhs;
    void print(FILE *fp);
};

struct ICmp : MachineInst {
    MachineOperand *lhs, *rhs;
    void print(FILE *fp);
};

struct FCmp : MachineInst {
    MachineOperand *lhs, *rhs;
    void print(FILE *fp);
    // add vmrs APSR_nzcv, FPSCR
};

struct IMov : MachineInst {
    MachineOperand *dst, *src;
    void print(FILE *fp);
};

struct FMov : MachineInst {
    MachineOperand *dst, *src;
    void print(FILE *fp);
};

struct Load : MachineInst {
    MachineOperand *dst, *base, *offset;
    // PostIndex adds index_length to the base after addressing
    // PreIndex adds index_length to the base before addressing
    enum Index { NoIndex, PostIndex, PreIndex };
    Index index_type = NoIndex;
    int index_length;
    void print(FILE *fp);
};

struct Store : MachineInst {
    MachineOperand *src, *base, *offset;
    // PostIndex adds index_length to the base after addressing
    // PreIndex adds index_length to the base before addressing
    enum Index { NoIndex, PostIndex, PreIndex };
    Index index_type = NoIndex;
    int index_length;
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

struct FCvt : MachineInst {
    MachineOperand *dst, *src;
    void print(FILE *fp);
};

struct Branch : MachineInst {
    std::string label;
    void print(FILE *fp);
};

struct Call : MachineInst {
    std::string callee;
    void print(FILE *fp);
};

struct Return : MachineInst {};

struct Push : MachineInst {
    std::vector<MReg *> regs;
};

struct Pop : MachineInst {
    std::vector<MReg *> regs;
};

struct MachineOperand {
    virtual char *print();
};

struct IImm : MachineOperand { 
    int value; 
    char *print();
};

struct FImm : MachineOperand { 
    float value; 
    char *print();
};

struct VReg : MachineOperand { 
    int id;
    char *print();
};

struct MReg : MachineOperand {
    enum Reg { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15,
               s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, 
               fp = r11, ip = r12, sp = r13, lr = r14, pc = r15, };
    Reg reg;
    char *print();
};

struct Symbol : MachineOperand {
    std::string name;
    char *print();
};