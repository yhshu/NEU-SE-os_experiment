cmake_minimum_required(VERSION 3.10)
project(os_experiment)

set(CMAKE_CXX_STANDARD 11)

add_executable(exp1 exp1/main.cpp)
add_executable(exp2 exp2/PCB.h exp2/PList.h exp2/main.cpp)
add_executable(exp3 exp3/1.cpp exp3/PTE.h)