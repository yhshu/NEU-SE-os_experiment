//
// Created by 舒意恒 on 2018/7/4.
//

#ifndef OS_EXPERIMENT_UFD_H
#define OS_EXPERIMENT_UFD_H

#include <string>

using namespace std;

struct UFDE { // user file directory entry
    string filename;
    int protect; // 保护码：允许读写执行为1，不允许读写执行为0
    int len; // 文件长度

    UFDE(string f, int p)
            : filename(f), protect(p), len(0) {}
};


#endif //OS_EXPERIMENT_UFD_H
