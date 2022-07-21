project(babel-fish)

cmake_minimum_required(VERSION 2.54)


set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR}/IR/include)
include_directories(${PROJECT_SOURCE_DIR}/IR/include/Types)
include_directories(${PROJECT_SOURCE_DIR}/IR/include/Instructions)

add_subdirectory(IR)

add_executable(IRtest.out IRtest.cc)
add_executable(dominator_tree.out dominator_tree.cc)

set_source_files_properties(lex.yy.c PROPERTIES LANGUAGE CXX)
set_source_files_properties(syntax_analyzer.tab.c PROPERTIES LANGUAGE CXX)

add_executable(check.out ast.h syntax_analyzer.tab.h lex.yy.c syntax_analyzer.tab.c ast.cc check.cc)

target_link_libraries(check.out PUBLIC IR)

target_link_libraries(IRtest.out PUBLIC IR)
target_link_libraries(dominator_tree.out PUBLIC IR)

