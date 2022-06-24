set(IR_SRC
    Types/Type.cc
    Types/PointerType.cc
    Types/IntegerType.cc
    Types/FloatType.cc
    Types/FunctionType.cc
    Instructions/Instruction.cc
    Instructions/ReturnInst.cc
    ConstantInt.cc
    Module.cc
    Value.cc 
    BasicBlock.cc
    Argument.cc
    Function.cc
    Use.cc
    User.cc
)

add_library(IR ${IR_SRC})
