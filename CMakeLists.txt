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

find_package(BISON)
bison_target(parser syntax_analyzer.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)

find_package(FLEX)
flex_target(lexer lexical_analyzer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)

add_flex_bison_dependency(lexer parser)

configure_file(${PROJECT_SOURCE_DIR}/ast.cc.in ${PROJECT_SOURCE_DIR}/ast.cc @ONLY)

#set_source_files_properties(lex.yy.c PROPERTIES LANGUAGE CXX)
#set_source_files_properties(syntax_analyzer.tab.c PROPERTIES LANGUAGE CXX)

add_executable(babel
               ast.h
               #syntax_analyzer.tab.h
               #lex.yy.c 
               #syntax_analyzer.tab.c
               ast.cc
               babel.cc
               arm.cpp
               ${BISON_parser_OUTPUTS}
               ${FLEX_lexer_OUTPUTS}
              )

target_link_libraries(babel PUBLIC IR)

