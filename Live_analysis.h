#pragma once
#include "arm.h"
struct LiveInterval{
    //std::vector<MachineInst*> insts;
    MReg* reg;
    int location   =   -1;
    int startpoint =   -1;
    int endpoint   =   -1;
};
using Vreg_LiveIntervalMap = std::map<VReg*,LiveInterval*> ;
using Vreg_LiveInterval    = std::pair<VReg*,LiveInterval*>;

VReg* get_inst_defs(MachineInst * inst){
    VReg* result;//store 指令的偏移可能为虚拟寄存器吗？？？
    if(auto i = dynamic_cast<Mov*>(inst)) {
        if(auto x = dynamic_cast<VReg*>(i->dst))
             result = x;
    }else if(auto i = dynamic_cast<Binary*>(inst)) {
       if(auto x =dynamic_cast<VReg*>(i->dst)){
             result = x;
        } 
    }
    else if(auto i = dynamic_cast<Cmp*>(inst)) {
    }
    else if(auto i = dynamic_cast<Store*>(inst)) {
        if(auto x =dynamic_cast<VReg*>(i->base)){
            result = x;
        }
    }
    else if(auto i = dynamic_cast<Load*>(inst)) {
        if(auto x =dynamic_cast<VReg*>(i->dst)){
            result = x;
        }
    }
    else if(auto i = dynamic_cast<IClz*>(inst)){
        if(auto x =dynamic_cast<VReg*>(i->dst)){
            result = x;
        }
    }
    else if(auto i = dynamic_cast<FNeg*>(inst)){
        if(auto x =dynamic_cast<VReg*>(i->dst)){
            result = x;
        }
    } 
    else if(auto i = dynamic_cast<Cvt*>(inst)) 
    {
        if(auto x =dynamic_cast<VReg*>(i->dst)){
            result = x;
        }
    }else{
    }
    return result;
}
std::vector<VReg*> get_inst_uses(MachineInst * inst){
    std::vector<VReg*> result;
    if(auto i = dynamic_cast<Mov*>(inst)) {
        if(auto x =dynamic_cast<VReg*>(i->src)){
            result.emplace_back(x);
        }
    }else if(auto i = dynamic_cast<Binary*>(inst)) {
        if(auto x = dynamic_cast<VReg*>(i->lhs)){
            result.emplace_back(x);
        }
        if(auto x = dynamic_cast<VReg*>(i->rhs)){
            result.emplace_back(x);
        }

    }
    else if(auto i = dynamic_cast<Cmp*>(inst)) {
        if(auto x = dynamic_cast<VReg*>(i->lhs)){
            result.emplace_back(x);
        }
        if(auto x = dynamic_cast<VReg*>(i->rhs)){
            result.emplace_back(x);
        }

    }
    else if(auto i = dynamic_cast<Store*>(inst)) {
        if(auto x = dynamic_cast<VReg*>(i->src)){
            result.emplace_back(x);
        }
        if(auto x = dynamic_cast<VReg*>(i->base)){
            result.emplace_back(x);
        }

    }
    else if(auto i = dynamic_cast<Load*>(inst)) {
        if(auto x = dynamic_cast<VReg*>(i->base)){
            result.emplace_back(x);
        }
        if(auto x = dynamic_cast<VReg*>(i->offset)){
            result.emplace_back(x);
        }
    }
    else if(auto i = dynamic_cast<IClz*>(inst)){
        if(auto x = dynamic_cast<VReg*>(i->src)){
            result.emplace_back(x);
        }

    }
    else if(auto i = dynamic_cast<FNeg*>(inst)){
        if(auto x = dynamic_cast<VReg*>(i->src)){
            result.emplace_back(x);
        }
    }
    else if(auto i = dynamic_cast<Cvt*>(inst))
    {
        if(auto x = dynamic_cast<VReg*>(i->src)){
            result.emplace_back(x);
        }
    }else{
    }
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
Vreg_LiveIntervalMap live_variable_analysis(MachineFunction * F,MachineOperand::OperandType ty=MachineOperand::Int){
    Init_live_variable(F);
    bool changing = true;
    while(changing){
        changing = false;
        for(auto bb:F->basic_blocks){
            auto inst = bb->insts.begin();
            while(inst != bb->insts.end()){
                auto p = ++inst;
                inst--;
                //计算out的内容
                for(auto var:*In[*p]){
                    if(var->operand_type !=ty) continue;
                    if(Out[*inst]->count(var) == 0){
                        changing = true;
                    }
                    Out[*inst]->insert(var);
                }
                //计算每条指令的In,In[s] = use[s] U (Out[s] -def[s])
                for(auto use:get_inst_uses(*inst)){
                    if(use->operand_type !=ty) continue;
                    if(In[*inst]->count(use) == 0){
                        changing = true;
                    }
                    In[*inst]->insert(use);
                }
                for(auto i:*Out[*inst]){
                    if(i->operand_type !=ty) continue;
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
    Vreg_LiveIntervalMap result;
    //为每一个虚拟寄存器生成一个到活性区间的映射
    for(auto bb:F->basic_blocks){
        for(auto inst:bb->insts){
            auto vrs =*In[inst];
            for(auto vr:vrs){
                if(vr->operand_type != ty){
                    continue;
                }
                if(result.count(vr) == 0){
                    result[vr] = new LiveInterval;
                    result[vr]->endpoint = result[vr]->startpoint = inst->number;
                }
                else{
                    if(result[vr]->endpoint < inst->number){
                        result[vr]->endpoint = inst->number;
                    }
                }
           }
        }
     }
     return result;
}   
std::vector<MachineOperand*> get_all_oprands(MachineInst* inst){
    std::vector<MachineOperand*> oprs;
    if(auto i = dynamic_cast<Mov*>(inst)) {
        oprs.emplace_back(i->src);
        oprs.emplace_back(i->dst);
    }else if(auto i = dynamic_cast<Binary*>(inst)) {
        oprs.emplace_back((i->lhs));
        oprs.emplace_back((i->rhs));
        oprs.emplace_back((i->dst));
    }
    else if(auto i = dynamic_cast<Cmp*>(inst)) {
        oprs.emplace_back((i->lhs));
        oprs.emplace_back((i->rhs));
    }
    else if(auto i = dynamic_cast<Store*>(inst)) {
        oprs.emplace_back((i->src));
        oprs.emplace_back((i->base));
        oprs.emplace_back((i->offset));
    }
    else if(auto i = dynamic_cast<Load*>(inst)) {
        oprs.emplace_back((i->base));
        oprs.emplace_back((i->offset));
        oprs.emplace_back((i->dst));
    }
    else if(auto i = dynamic_cast<IClz*>(inst)){
        oprs.emplace_back((i->dst));
        oprs.emplace_back((i->src));
    }
    else if(auto i = dynamic_cast<FNeg*>(inst)){
        oprs.emplace_back((i->dst));
        oprs.emplace_back((i->src));
    } 
    else if(auto i = dynamic_cast<Cvt*>(inst)) 
    {
        oprs.emplace_back((i->dst));
        oprs.emplace_back((i->src));
    }
    return oprs;
 }
