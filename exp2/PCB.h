//
// Created by 舒意恒 on 2018/6/29.
//

#ifndef OS_EXPERIMENT_PCB_H
#define OS_EXPERIMENT_PCB_H

#define PCB_READY 'R'   // 就绪状态，是初始状态
#define PCB_WORKING 'W' // 运行状态
#define PCB_FINISH 'E'  // 完成状态

class PCB {
public:
    string name;   // 进程名
    PCB *next;    // 指针：指向下一个进程的 PCB 首地址，最后一个进程的指针为0
    int needTime;  // 要求运行时间
    int priority; // 优先数：优先数大的进程优先
    char state;    // 状态

    PCB(char name, int time, int pri) : name(name), needTime(time), priority(pri) {}

    void run() {
        priority--;
        needTime--;
    }
};


#endif //OS_EXPERIMENT_PCB_H
