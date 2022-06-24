set(IR_SRC
    Value.cc 
    Types/Type.cc
    Use.cc
    User.cc
)

include_directories(${PROJECT_SOURCE_DIR}/IR/include)

add_library(IR ${IR_SRC})
