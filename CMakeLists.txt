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

target_link_libraries(IRtest.out PUBLIC IR)
