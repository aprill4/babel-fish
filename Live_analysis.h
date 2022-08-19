#pragma once
#include "arm.h"

VReg* get_inst_defs(MachineInst * inst){
    VReg* result;
    return result;
}
std::vector<VReg*> get_inst_uses(MachineInst * inst){
    std::vector<VReg*> result;
    return result;
}
std::map<MachineInst*,std::set<VReg*>*> In;
std::map<MachineInst*,std::set<VReg*>*> Out;
void Init_live_variable(MachineFunction * F){
    for(auto bb:F->basic_blocks){
        for(auto inst:bb->insts){
            In[inst]  = new std::set<VReg*>;
            Out[inst] = new std::set<VReg*>; 
        }
    }
}
void live_variable_analysis(MachineFunction * F){
    bool changing = true;
    while(changing){
        changing = false;
        for(auto bb:F->basic_blocks){
            auto inst = bb->insts.begin();
            while(inst != bb->insts.end()){
                auto p = ++inst;
                inst--;
                for(auto var:*In[*p]){
                    if(Out[*inst]->count(var) == 0){
                        changing = true;
                    }
                    Out[*inst]->insert(var);
                }
                for(auto use:get_inst_uses(*inst)){
                    if(In[*inst]->count(use) == 0){
                        changing = true;
                    }
                    In[*inst]->insert(use);
                }
                for(auto i:*Out[*inst]){
                    if(get_inst_defs(*inst) != i){
                        if(In[*inst]->count(i) == 0){
                            changing = true;
                        }
                        In[*inst]->insert(i);
                    }
                }
            }
        }
    }
}
