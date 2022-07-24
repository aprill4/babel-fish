#pragma once

#include <list>
#include <vector>

struct MachineModule {
    std::vector<MachineFunction *> functions;
};

struct MachineFunction {
    std::vector<MachineBasicBlock *> basic_blocks;
};

struct MachineBasicBlock {
    std::vector<MachineBasicBlock *> pres, sucs;
    std::list<MachineInst *> insts;
};

struct MachineInst {
    enum Cond { NoCond, Le, Lt, Ge, Gt, Eq, Ne };
    Cond cond = NoCond;

    enum FlexibleShift { NoShift, Lsl, Lsr, Asl, Asr };
    FlexibleShift shift_type = NoShift;
    int shift_length;
};

struct MachineOperand {};

struct IImm : MachineOperand { int value; };
struct FImm : MachineOperand { float value; };
struct VReg : MachineOperand { int id; };

struct MReg : MachineOperand {
    enum Reg { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15,
               s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, 
               // aliases
               // special registers
    };
    Reg reg;
};

struct Symbol : MachineOperand {
    std::string name;
};

struct Binary : MachineInst {
    enum Op { IAdd, ISub, IMul, IDiv, FAdd, FSub, FMul, FDiv, ILsl, ILsr, IAsl, IAsr };
    Op kind;
    MachineOperand *dst, *lhs, *rhs;
};

struct ICmp : MachineInst {
    MachineOperand *lhs, *rhs;
};

struct FCmp : MachineInst {
    MachineOperand *lhs, *rhs;
    // add vmrs APSR_nzcv, FPSCR
};

struct IMov : MachineInst {
    MachineOperand *dst, *src;
};

struct FMov : MachineInst {
    MachineOperand *dst, *src;
};

struct Load : MachineInst {
    MachineOperand *dst, *base, *offset;
    // PostIndex adds index_length to the base after addressing
    // PreIndex adds index_length to the base before addressing
    enum Index { NoIndex, PostIndex, PreIndex };
    Index index_type = NoIndex;
    int index_length;
};

struct Store : MachineInst {
    MachineOperand *src, *base, *offset;
    // PostIndex adds index_length to the base after addressing
    // PreIndex adds index_length to the base before addressing
    enum Index { NoIndex, PostIndex, PreIndex };
    Index index_type = NoIndex;
    int index_length;
};

struct IClz : MachineInst {
    MachineOperand *dst, *src;
};

struct FNeg : MachineInst {
    MachineOperand *dst, *src;
};

struct FCvt : MachineInst {
    MachineOperand *dst, *src;
};

struct Branch : MachineInst {
    std::string label;
};

struct Call : MachineInst {
    std::string callee;
};

struct Return : MachineInst {};

struct Push : MachineInst {
    std::vector<MReg *> regs;
};

struct Pop : MachineInst {
    std::vector<MReg *> regs;
};