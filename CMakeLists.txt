project(babel-fish)

cmake_minimum_required(VERSION 2.54)

add_subdirectory(IR)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR}/IR/include)
include_directories(${PROJECT_SOURCE_DIR}/IR/include/Types)
include_directories(${PROJECT_SOURCE_DIR}/IR/include/Instructions)

add_executable(IRtest IRtest.cc)
target_link_libraries(IRtest PUBLIC IR)
