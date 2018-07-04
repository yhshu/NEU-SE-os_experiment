//
// Created by 舒意恒 on 2018/7/4.
//

#ifndef OS_EXPERIMENT_MFD_H
#define OS_EXPERIMENT_MFD_H

#include <string>
#include "UFDE.h"

using namespace std;

struct MFDE { // 主文件目录 main file directory entry
    string username; // 用户名
    vector<UFDE> UFD; // 文件目录指针

    MFDE(string u) : username(u) {}
};


#endif //OS_EXPERIMENT_MFD_H
