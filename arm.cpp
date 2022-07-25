#include "arm.h"
#include "IR.h"


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

// MachineOperand
char* MachineOperand::print_shift() {
    char *shift_str[] = {
        "", "lsl", "lsr", "asr", "ror"
    };

    char *str = new char[20];
    if (shift_type != NoShift) {
        sprintf(str, ", %s #%d\n", shift_str[shift_type], shift_length);
        return str;
    }

    return "\n";
}

char *IImm::print() {
    char *str = new char[12];
    sprintf(str, "#%d", value);
    return str;
}

char *FImm::print() {
    char *str = new char[20];
    sprintf(str, "#%e", value);
    return str;
}

char *VReg::print() {
    char *str = new char[12];
    sprintf(str, "v%d", id);
    return str;
}

char *MReg::print() {
    char *mreg_str[] = {
        "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15",
        "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "s12", "s13", "s14", "s15",
    };

    return mreg_str[reg];
}

char *Symbol::print() {
    return (char *)name.c_str();
}


char *MachineInst::get_cond() {
    char *cond_str[] = {
        "", "le", "lt", "ge", "gt", "eq", "ne"
    };
    return cond_str[cond];

}

void Binary::print(FILE *fp) {
    char *op_str[] = {
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
        fprintf(fp, "movw%s %s, #:lower:%s", dst->print(), src->print());
        fprintf(fp, "movt%s %s, #:upper:%s", dst->print(), src->print());
    } else {
        fprintf(fp, "mov%s %s, %s", get_cond(), dst->print(), src->print());
    }
}

void FMov::print(FILE *fp) {
    if (dynamic_cast<Symbol *>(src)) {
        fprintf(fp, "movw%s %s, #:lower:%s", dst->print(), src->print());
        fprintf(fp, "movt%s %s, #:upper:%s", dst->print(), src->print());
    } else {
        fprintf(fp, "vmov.f32%s %s, %s", get_cond(), dst->print(), src->print());
    }
}

void ILoad::print(FILE *fp) {
    switch (index_type) {
        case PreIndex:
            fprintf(fp, "ldr%s %s, [%s, %s]!", get_cond(), dst->print(), base->print(), index->print());
            break;
        case PostIndex:
            fprintf(fp, "ldr%s %s, [%s], #%s", get_cond(), dst->print(), base->print(), offset);
    }
}

void IStore::print(FILE *fp) {

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

void emit_asm (MachineModule *mm, FILE *fp) {
    mm->print(fp);
}