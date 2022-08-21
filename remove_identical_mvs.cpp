#include "pass.h"

void remove_identical_mvs(MachineModule *m) {
    for (auto mf: m->functions) {
        for (auto mbb: mf->basic_blocks) {
            for (auto it = mbb->insts.begin(); it != mbb->insts.end(); it++) {

                if (it == mbb->insts.begin()) {
                    continue;
                }

                auto prev = std::prev(it, 1);
                auto mv = dynamic_cast<Mov *>(*it);

                if (mv) {
                    auto src = dynamic_cast<MReg *>(mv->src);
                    auto dst = dynamic_cast<MReg *>(mv->dst);

                    if (src && dst && (src->reg == dst->reg)) {
                        mbb->insts.erase(it);
                        it = prev;
                    }
                } 
            }
        }
    }
}
