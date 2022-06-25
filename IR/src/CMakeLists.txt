set(IR_SRC
    Types/Type.cc
    Types/PointerType.cc
    Types/IntegerType.cc
    Types/ArrayType.cc
    Types/FunctionType.cc
    Instructions/Instruction.cc
    Instructions/AllocaInst.cc
    Instructions/BranchInst.cc
    Instructions/LoadInst.cc
    Instructions/StoreInst.cc
    Instructions/BinaryInst.cc
    Instructions/IcmpInst.cc
    Instructions/FcmpInst.cc
    Instructions/ReturnInst.cc
    Instructions/GetElementPtrInst.cc
    ConstantInt.cc
    Module.cc
    Value.cc 
    BasicBlock.cc
    Argument.cc
    Context.cc
    Function.cc
    Use.cc
    User.cc
)

add_library(IR ${IR_SRC})
