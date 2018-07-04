cmake_minimum_required(VERSION 3.10)
project(os_experiment)

set(CMAKE_CXX_STANDARD 11)

add_executable(exp1 exp1/exp1.cpp)
add_executable(exp2 exp2/exp2.cpp exp2/PCB.h exp2/PList.h)
add_executable(exp3.1 exp3/exp3.1.cpp exp3/PTE.h exp3/operation.txt)
add_executable(exp4.1 exp4/exp4.1.cpp exp4/MFDE.h exp4/UFDE.h exp4/AFDE.h)
add_executable(exp4.2 exp4/exp4.2.cpp exp4/TreeNode.h)