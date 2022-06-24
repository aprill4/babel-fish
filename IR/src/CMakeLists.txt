set(IR_SRC
    Types/Type.cc
    Types/PointerType.cc
    Types/IntegerType.cc
    Types/FunctionType.cc
    Module.cc
    Value.cc 
    Function.cc
    Use.cc
    User.cc
)

add_library(IR ${IR_SRC})
