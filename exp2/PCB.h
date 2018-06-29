//
// Created by 舒意恒 on 2018/6/29.
//

#ifndef OS_EXPERIMENT_PCB_H
#define OS_EXPERIMENT_PCB_H

using namespace std;

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
    int roundTime; // 周转时间：从进程提交到进程完成的时间长度
    int waitingTime; // 等待时间：在就绪队列中等待所花费的时间之和

    PCB(string, int, int);

    void run();

    string getState();
};

PCB::PCB(string name, int time, int pri) : name(name), needTime(time), priority(pri),
                                           state(PCB_READY), next(nullptr), roundTime(0),
                                           waitingTime(0) {
}

void PCB::run() {
    this->priority--;
    this->needTime--;
    this->state = PCB_WORKING;
}

string PCB::getState() {
    if (this->state == PCB_READY)
        return "ready";
    else if (this->state == PCB_WORKING)
        return "working";
    else if (this->state == PCB_FINISH)
        return "finish";
}

#endif //OS_EXPERIMENT_PCB_H
