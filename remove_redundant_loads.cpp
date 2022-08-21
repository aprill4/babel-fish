#include "pass.h"

void remove_redundant_loads(MachineModule *m) {
    for (auto mf: m->functions) {
        for (auto mbb: mf->basic_blocks) {
            for (auto it = mbb->insts.begin(); it != mbb->insts.end(); it++) {
                auto next = std::next(it, 1);
                if (next == mbb->insts.end()) {
                    break;
                }

                auto cur_store = dynamic_cast<Store *>(*it);
                auto next_load = dynamic_cast<Load *>(*next);
                //auto cur_load = dynamic_cast<Load *>(*it);
                //auto next_store = dynamic_cast<Store *>(*next);
                if (cur_store && next_load) {
                    auto str_base = dynamic_cast<MReg *>(cur_store->base);
                    auto ldr_base = dynamic_cast<MReg *>(next_load->base);

                    if (str_base->reg == ldr_base->reg) {
                        if (!cur_store->offset && !next_load->offset) {
                            auto mv = new Mov(next_load->dst, cur_store->src);
                            bool is_float = next_load->dst->operand_type == MachineOperand::Float;
                            mv->tag = is_float ? Mov::F2F : Mov::I2I;
                            mbb->insts.insert(it, mv);
                            mbb->insts.erase(next);

                        } else if (cur_store->offset && next_load->offset) {
                            auto str_off_mreg = dynamic_cast<MReg *>(cur_store->offset);
                            auto ldr_off_mreg = dynamic_cast<MReg *>(next_load->offset);

                            auto str_off_imm = dynamic_cast<IImm *>(cur_store->offset);
                            auto ldr_off_imm = dynamic_cast<IImm *>(next_load->offset);

                            bool is_mreg = str_off_mreg && ldr_off_mreg;
                            bool is_imm = str_off_imm && ldr_off_imm;

                            if ((is_mreg && (str_off_mreg->reg == ldr_off_mreg->reg)) || 
                                (is_imm && (str_off_imm->value == ldr_off_imm->value))) {
                                
                                // printf("%d\n", str_base->reg);
                                auto mv = new Mov(next_load->dst, cur_store->src);
                                bool is_float = next_load->dst->operand_type == MachineOperand::Float;
                                mv->tag = is_float ? Mov::F2F : Mov::I2I;
                                mbb->insts.insert(it, mv);

                                mbb->insts.erase(next);
                            }
                        }

                    }
                } 
            }
        }
    }
}
