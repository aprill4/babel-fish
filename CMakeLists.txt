project(babel-fish)

cmake_minimum_required(VERSION 2.54)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR}/IR/include)
include_directories(${PROJECT_SOURCE_DIR}/IR/include/Types)
include_directories(${PROJECT_SOURCE_DIR}/IR/include/Instructions)

add_subdirectory(IR)

# add_executable(IRtest.out IRtest.cc)
# add_executable(dominator_tree.out dominator_tree.cc)
# add_executable(arm.out arm.cpp)

set_source_files_properties(lex.yy.c PROPERTIES LANGUAGE CXX)
set_source_files_properties(syntax_analyzer.tab.c PROPERTIES LANGUAGE CXX)

add_executable(check.out ast.h syntax_analyzer.tab.h lex.yy.c syntax_analyzer.tab.c ast.cc check.cc arm.cpp)
add_executable(arm_test ast.h syntax_analyzer.tab.h lex.yy.c syntax_analyzer.tab.c ast.cc arm_test.cc arm.cpp)

target_link_libraries(check.out PUBLIC IR)
target_link_libraries(arm_test PUBLIC IR)

# target_link_libraries(IRtest.out PUBLIC IR)
#target_link_libraries(dominator_tree.out PUBLIC IR)
#target_link_libraries(arm.out PUBLIC IR)

