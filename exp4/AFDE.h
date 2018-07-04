//
// Created by 舒意恒 on 2018/7/4.
//

#ifndef OS_EXPERIMENT_AFDE_H
#define OS_EXPERIMENT_AFDE_H

struct AFDE { // 打开文件目录表项
    string filename; // 打开文件名
    int protect; // 打开保护码
    int read; // 读指针
    int write; // 写指针
    AFDE(string f, int p) :
            filename(f), protect(p), read(0), write(0) {}
};


#endif //OS_EXPERIMENT_AFDE_H
