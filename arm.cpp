#include "arm.h"
#include "IR.h"

char *mreg_str[] = {
    "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15",
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "s12", "s13", "s14", "s15",
    "fp", "ip", "sp", "lr", "pc"
};

void MachineModule::print(FILE *fp) {
    for (auto func: functions) {
        func->print(fp);
    }
}

void MachineFunction::print(FILE *fp) {
    for (auto bb: basic_blocks) {
        bb->print(fp);
    }
}

void MachineBasicBlock::print(FILE *fp) {
    for (auto inst: insts) {
        inst->print(fp);
    }
}

char *IImm::print() {
}

char *FImm::print() {
    //char *str = '#' + 
    //return str;
}

char *VReg::print() {
    //char *str = 
}

void Binary::print(FILE *fp) {
    char *op_str[] = {
        "add", "sub", "mul", "div", "fadd", "fsub", "fmul", "fdiv", "lsl", "lsr", "asl", "asr"
    };
    fprintf(fp, "%s %s, %s, %s\n", op_str[kind], mreg_str[(MReg *)dst->reg], lhs->name.c_str(), rhs->name.c_str());
}

void emit_asm (MachineModule *mm) {
    mm->print();
}