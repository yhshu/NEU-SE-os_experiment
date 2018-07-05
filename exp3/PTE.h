//
// Created by 舒意恒 on 2018/7/3.
//

#ifndef OS_EXPERIMENT_PAGETABLE_H
#define OS_EXPERIMENT_PAGETABLE_H


class PTE { // 页表项 page table entry
public:
    int number;
    int mark; // 1 已在主存；0 未在主存
    int memoryBlock; // 在主存上的块号
    int diskLocation; // 在磁盘上的位置
    int modifyMark; // 1 修改过；0 未修改

    PTE(int n, int m, int d)
            : number(n), mark(m), memoryBlock(0), diskLocation(d), modifyMark(0) {}

    PTE(int n, int ma, int me, int d)
            : number(n), mark(ma), memoryBlock(me), diskLocation(d), modifyMark(0) {}

};


#endif //OS_EXPERIMENT_PAGETABLE_H
